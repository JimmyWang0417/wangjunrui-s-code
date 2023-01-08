#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
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
constexpr int N = 11879572 + 5;
constexpr int mod = 998244353, inv2 = (mod + 1) / 2;
ll fac[N], ifac[N];
inline ll C(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int n, m;
int a[N];
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
ll f[N], g[N];
int tot = 0;
int poly[N * 8];
int *mp = poly + N;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    read(n, m);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    ll inv = quickpow(inv2, n);
    for (int i = n; i >= 1; --i)
    {
        if ((i & 1) == (n & 1))
            f[i] = C(n, (n + i) >> 1) * inv % mod;
        g[i] = (g[i + 1] + f[i]) % mod;
    }
    for (int i = 1; i <= n; ++i)
        (f[i] += g[i + 1] * 2) %= mod;
    int minn = INT_MAX, maxx = INT_MIN;
    for (int i = 1; i <= m; ++i)
    {
        read(a[i]);
        ckmin(minn, a[i] - n);
        ckmax(maxx, a[i] + n);
    }
    for (int i = minn; i <= maxx; ++i)
        mp[i] = 1;
    for (int i = 1; i <= m; ++i)
    {
        mp[a[i]] = 0;
        for (int j = 1; j <= n; ++j)
        {
            (mp[a[i] - j] = (int)((ll)mp[a[i] - j] * (1 - f[j]) % mod)) %= mod;
            (mp[a[i] + j] = (int)((ll)mp[a[i] + j] * (1 - f[j]) % mod)) %= mod;
        }
    }
    ll res = 0;
    for (int i = minn; i <= maxx; ++i)
        (res += (1 - mp[i])) %= mod;
    printf("%lld\n", (res + mod) % mod);
    return 0;
}
