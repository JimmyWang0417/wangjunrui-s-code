/**
 *    unicode: UTF-8
 *    name:    CF813D Two Melodies
 *    author:  whitepaperdog
 *    created: 2022.07.10 周日 20:10:37 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 5005, M = 1e5 + 5;
int n, a[N];
int dp[N][N];
int f[M], g[7];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    int res = 0;
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            ckmax(f[a[j]], dp[j][i]);
            ckmax(g[a[j] % 7], dp[j][i]);
        }
        for (int j = i + 1; j <= n; ++j)
        {
            dp[i][j] = max(max(f[a[j] - 1], f[a[j] + 1]), max(g[a[j] % 7], dp[0][i])) + 1;
            ckmax(f[a[j]], dp[i][j]);
            ckmax(g[a[j] % 7], dp[i][j]);
            ckmax(res, dp[i][j]);
        }
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
    }
    printf("%d\n", res);
    return 0;
}