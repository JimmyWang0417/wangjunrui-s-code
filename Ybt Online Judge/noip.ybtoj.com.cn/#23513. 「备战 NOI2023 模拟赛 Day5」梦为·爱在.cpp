#include "iwill.h"
#include <random>
#include <tuple>
using namespace std;
constexpr int N = 10005;
constexpr int M = 35;
constexpr int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
constexpr int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int a[N][M][M], b[N][M][M];
int n;
tuple<int, int, int> c[N];
bool vis[M][M];
void sweep(int W, int H, int K)
{
    for (int S = 100; S <= 10000; ++S)
    {
        int T = S, cnt = 0;
        for (int i = 1;; ++i)
        {
            T = (int)(48271ll * T % 2147483647);
            if (!a[S][T / H % W][T % H])
            {
                a[S][T / H % W][T % H] = 1;
                ++cnt;
            }
            if (cnt == K)
                break;
        }
        for (int i = 0; i < W; ++i)
            for (int j = 0; j < H; ++j)
            {
                if (a[S][i][j])
                {
                    b[S][i][j] = -1;
                    continue;
                }
                for (int d = 0; d < 8; ++d)
                {
                    int x = i + dx[d], y = j + dy[d];
                    if (x < 0 || x >= W || y < 0 || y >= H)
                        continue;
                    b[S][i][j] += a[S][x][y];
                }
            }
    }
    mt19937 rnd((random_device())());
    for (int i = 1, j = 0; j < 6; ++i)
    {
        int x = uniform_int_distribution<>(0, W - 1)(rnd), y = uniform_int_distribution<>(0, H - 1)(rnd);
        if (vis[x][y])
            continue;
        vis[x][y] = 1;
        c[++n] = make_tuple(x, y, open(x, y));
        if (get<2>(c[n]) == -1)
            ++j;
    }
    for (int S = 100; S <= 10000; ++S)
    {
        bool flag = 1;
        for (int i = 1; i <= n; ++i)
        {
            int x, y, z;
            tie(x, y, z) = c[i];
            if (b[S][x][y] != z)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            for (int i = 0; i < W; ++i)
                for (int j = 0; j < H; ++j)
                    if (!a[S][i][j] && !vis[i][j])
                        open(i, j);
            return;
        }
    }
    return;
}
