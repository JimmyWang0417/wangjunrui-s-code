/**
 *    unicode: UTF-8
 *    name:    P5326 [ZJOI2019]开关
 *    author:  whitepaperdog
 *    created: 2022.08.06 周六 21:25:09 (Asia/Shanghai)
 **/
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
constexpr int M = 5e4 + 5;
constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
inline ll quickpow(ll a, int b)
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
int n, m, p[N], s[N];
ll _a[N][M * 2], *a[N];
ll _b[N][M * 2], *b[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(s[i]);
    for (int i = 0; i <= n; ++i)
    {
        a[i] = &_a[i][M];
        b[i] = &_b[i][M];
    }
    a[0][0] = b[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        read(p[i]);
        for (int j = -m; j <= m; ++j)
        {
            (a[i][j + p[i]] += (ll)inv2 * a[i - 1][j]) %= mod;
            if (s[i])
                (a[i][j - p[i]] -= (ll)inv2 * a[i - 1][j]) %= mod;
            else
                (a[i][j - p[i]] += (ll)inv2 * a[i - 1][j]) %= mod;
            (b[i][j + p[i]] += (ll)inv2 * b[i - 1][j]) %= mod;
            (b[i][j - p[i]] += (ll)inv2 * b[i - 1][j]) %= mod;
        }
        m += p[i];
    }
    ll res = 0;
    for (int i = -m; i < m; ++i)
        (res += (a[n][i] * b[n][m] - a[n][m] * b[n][i]) % mod *
                quickpow(b[n][m] * b[n][m] % mod * (i * quickpow(m, mod - 2) % mod - 1) % mod, mod - 2) % mod) %= mod;
    printf("%lld\n", (res + mod) % mod);
    return 0;
}