/**
 *    unicode: UTF-8
 *    name:    CF713D Animals and Puzzle
 *    author:  wangjunrui
 *    created: 2022.06.29 周三 00:43:05
 **/
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
    bool dp = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            dp = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar();
    }
    if (dp)
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
constexpr int N = 1005;
int n, m, q, a[N][N];
int dp[10][10][N][N], Log[N];
inline int query(int x1, int y1, int x2, int y2)
{
    int i = Log[x2 - x1 + 1], j = Log[y2 - y1 + 1];
    return max(max(dp[i][j][x1][y1], dp[i][j][x2 - (1 << i) + 1][y1]),
               max(dp[i][j][x1][y2 - (1 << j) + 1], dp[i][j][x2 - (1 << i) + 1][y2 - (1 << j) + 1]));
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            read(a[i][j]);
            if (a[i][j] == 1)
                dp[0][0][i][j] = min(min(dp[0][0][i - 1][j], dp[0][0][i][j - 1]), dp[0][0][i - 1][j - 1]) + 1;
        }
    Log[0] = -1;
    for (int i = 1; i <= n || i <= m; ++i)
        Log[i] = Log[i >> 1] + 1;
    for (int k = 0; k <= Log[n]; ++k)
        for (int l = 0; l <= Log[m]; ++l)
            if (k | l)
                for (int i = 1; i + (1 << k) - 1 <= n; ++i)
                    for (int j = 1; j + (1 << l) - 1 <= m; ++j)
                    {
                        if (k)
                            dp[k][l][i][j] = max(dp[k - 1][l][i][j], dp[k - 1][l][i + (1 << (k - 1))][j]);
                        else
                            dp[k][l][i][j] = max(dp[k][l - 1][i][j], dp[k][l - 1][i][j + (1 << (l - 1))]);
                    }
    read(q);
    while (q--)
    {
        int x1, y1, x2, y2;
        read(x1, y1, x2, y2);
        int l = 1, r = min(x2 - x1 + 1, y2 - y1 + 1);
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (query(x1 + mid - 1, y1 + mid - 1, x2, y2) >= mid)
                l = mid + 1;
            else
                r = mid - 1;
        }
        printf("%d\n", r);
    }
    return 0;
}