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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 4005;
constexpr int mod = 998244353;
inline int quickpow(ll a, int b = mod - 2)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return (int)res;
}
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
template <typename T>
inline void dec(T &x, T y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int m, n;
int a[N], b[N];
int f[N][N], g[N][N], s[N][N];
int answer[N];
int pre[N], suf[N];
signed main()
{
    read(m, n);
    int sum = 0;
    for (int i = 0; i <= m; ++i)
    {
        read(a[i]);
        add(sum, a[i]);
    }
    ll times = 1;
    for (int i = 1; i <= n; ++i)
    {
        read(b[i]);
        (times *= b[i]) %= mod;
    }
    int inv = quickpow(sum, mod - 2);
    f[0][0] = (int)((ll)a[0] * inv % mod);
    for (int i = 1; i <= m; ++i)
    {
        f[0][i] = f[0][i - 1];
        add(f[0][i], (int)((ll)a[i] * inv % mod));
    }
    for (int i = 1; i <= n; ++i)
    {
        int del = quickpow(f[i - 1][i - 1], b[i]);
        for (int j = i; j <= m; ++j)
        {
            f[i][j] = quickpow(f[i - 1][j], b[i]);
            dec(f[i][j], del);
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0, las = 0; j <= m; ++j)
        {
            dec(s[i][j], las);
            add(s[i][j], las = quickpow(f[i][j], b[i + 1] - 1));
        }
    for (int i = n; i <= m; ++i)
        g[n][i] = 1;
    for (int i = n - 1; i >= 0; --i)
    {
        pre[0] = s[i][0];
        for (int j = 1; j <= m; ++j)
        {
            pre[j] = pre[j - 1];
            add(pre[j], s[i][j]);
        }
        for (int j = m; j >= 0; --j)
        {
            suf[j] = suf[j + 1];
            add(suf[j], (int)((ll)s[i][j] * g[i + 1][j] % mod));
        }
        for (int j = i; j <= m; ++j)
            g[i][j] = (int)(((ll)g[i + 1][j] * pre[j] + suf[j + 1]) % mod);
    }
    for (int i = 0; i <= m; ++i)
        printf("%lld\n", g[0][i] * times % mod * a[i] % mod * inv % mod);
    return 0;
}