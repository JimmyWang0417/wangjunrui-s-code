#include <algorithm>
#include <cstdio>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(x) (x & (-x))
template <typename T>
inline void read(T &x)
{
    x = 0;
    char s = (char)getchar();
    bool f = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            f = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar();
    }
    if (f)
        x = (~x) + 1;
}
template <typename T, typename... T1>
inline void read(T &x, T1 &...x1)
{
    read(x);
    read(x1...);
}
template <typename T>
inline void ckmin(T &x, T y)
{
    if (x > y)
        x = y;
}
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
using namespace std;
constexpr int N = 105;
int n, m;
int sum[N][N];
char str[N];
int dp[N][N][N][N];
inline int calc(int x1, int y1, int x2, int y2)
{
    return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}
signed main()
{
    read(n, m);
    int wherex = 0, wherey = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str + 1);
        for (int j = 1; j <= m; ++j)
        {
            if (str[j] == 'E')
            {
                wherex = i;
                wherey = j;
            }
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (str[j] == 'o');
        }
    }
    int res = 0;
    for (int u = 0; u < wherex; ++u)
        for (int d = 0; wherex + d <= n; ++d)
            for (int l = 0; l < wherey; ++l)
                for (int r = 0; wherey + r <= m; ++r)
                {
                    ckmax(res, dp[u][d][l][r]);
                    const int &now = dp[u][d][l][r];

                    if (u + d < wherex - 1)
                        ckmax(dp[u + 1][d][l][r], now + calc(wherex - u - 1, max(wherey - l, r + 1), wherex - u - 1, min(wherey + r, m - l)));
                    if (u + d < n - wherex)
                        ckmax(dp[u][d + 1][l][r], now + calc(wherex + d + 1, max(wherey - l, r + 1), wherex + d + 1, min(wherey + r, m - l)));
                    if (l + r < wherey - 1)
                        ckmax(dp[u][d][l + 1][r], now + calc(max(wherex - u, d + 1), wherey - l - 1, min(wherex + d, n - u), wherey - l - 1));
                    if (l + r < m - wherey)
                        ckmax(dp[u][d][l][r + 1], now + calc(max(wherex - u, d + 1), wherey + r + 1, min(wherex + d, n - u), wherey + r + 1));
                }
    printf("%d\n", res);
    return 0;
}