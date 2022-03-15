// Problem: Strange Functions
// Contest: CodeChef - ICPC Preparatory Series by Team Horcruxes
// URL: https://www.codechef.com/IPC15P2B/problems/STR_FUNC
// Memory Limit: 256 MB
// Time Limit: 2500 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
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
constexpr int N = (1 << 20) + 5;
constexpr int mod = 1e9 + 7;
int n, a[N];
ll dp[2][N][25];
ll f[N], g[N];
inline void work()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 20; ++j)
            if ((i >> j) & 1)
            {
                dp[0][i][j + 1] = (dp[0][i][j] + dp[0][i ^ (1 << j)][j]) % mod;
                dp[1][i][j + 1] = (dp[1][i][j] + dp[1][i ^ (1 << j)][j]) % mod;
            }
            else
            {

                dp[0][i][j + 1] = dp[0][i][j];
                dp[1][i][j + 1] = dp[1][i][j];
            }
        f[i] = ((ll)a[i] * a[i] + dp[1][i][20] * dp[1][i][20]) % mod;
        g[i] = (f[i] * f[i] + dp[0][i][20]) % mod;
        for (int j = 0; j < 20; ++j)
        {
            (dp[0][i][j] += f[i] * f[i]) %= mod;
            (dp[1][i][j] += g[i]) %= mod;
        }
    }
}
signed main()
{
    read(n);
    for (int i = 0; i < n; ++i)
        read(a[i]);
    work();
    ll ans = 0;
    for (int i = 0; i < n; ++i)
        (ans += i * f[i] % mod * g[i]) %= mod;
    printf("%lld\n", ans);
    return 0;
}