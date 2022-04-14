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
int f[N][N], g[N];
int answer[N];
signed main()
{
    read(m, n);
    int sum = 0;
    for (int i = 0; i <= m; ++i)
    {
        read(a[i]);
        add(sum, a[i]);
    }
    for (int i = 1; i <= n; ++i)
        read(b[i]);
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
    g[m] = 1;
    for (int i = n; i >= 1; i--)
    {
        int res = 0;
        for (int j = i; j <= m; j++)
        {
            add(res, g[j]);
            g[j] = (int)((ll)b[i] * g[j] % mod * quickpow(f[i - 1][j], b[i] - 1) % mod);
        }
        dec(g[i - 1], (int)((ll)b[i] * res % mod * quickpow(f[i - 1][i - 1], b[i] - 1) % mod));
    }
    for (int i = m; i >= 0; --i)
    {
        answer[i] = answer[i + 1];
        add(answer[i], g[i]);
    }
    for (int i = 0; i <= m; ++i)
        printf("%lld\n", ((ll)answer[i] * a[i] % mod * inv % mod + mod) % mod);
    return 0;
}