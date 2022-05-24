#include <bits/stdc++.h>
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
constexpr int N = 2005;
constexpr int mod = 1e9 + 7;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline ll quickpow(ll a, int b = mod - 2)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
int n, m;
ll fac[N * N], ifac[N * N];
inline ll C(int x, int y)
{
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
ll dp[N][N];
signed main()
{
    read(n, m);
    if (m == 1)
    {
        printf("1\n");
        return 0;
    }
    fac[0] = 1;
    for (int i = 1; i <= n * m; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n * m] = quickpow(fac[n * m]);
    for (int i = n * m; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    dp[0][0] = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= i; ++j)
        {
            if (i == n && j == n)
                continue;
            add(dp[i + 1][j], dp[i][j]);
            (dp[i][j + 1] += dp[i][j] * (n - j) % mod * C(n * m - i - (m - 1) * j - 1, m - 2)) %= mod;
        }
    printf("%lld\n", dp[n][n]);
    return 0;
}