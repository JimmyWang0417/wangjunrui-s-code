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
constexpr int N = 2e6 + 5;
constexpr int mod = 998244353;
inline ll quickpow(ll a, int b = mod - 2, int p = mod)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}
ll fac[N], inv[N];
inline ll C(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return fac[n] * inv[n - m] % mod * inv[m] % mod;
}
ll f[N];
ll pre[N], suf[N];
inline ll lagrange(int x, int m)
{
    pre[0] = 1;
    for (int i = 1; i <= m; ++i)
        pre[i] = pre[i - 1] * (x - i) % mod;
    suf[m + 1] = 1;
    for (int i = m; i >= 1; --i)
        suf[i] = suf[i + 1] * (x - i) % mod;
    ll ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        ll a = pre[i - 1] * suf[i + 1] % mod, b = fac[i - 1] * fac[m - i] % mod * ((m - i) & 1 ? -1 : 1);
        (ans += f[i] * a % mod * quickpow(b, mod - 2) % mod) %= mod;
    }
    return (ans + mod) % mod;
}
int n, m, k;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdout);
#endif
    read(n, m, k);

    int nmsl = min(k, n + m), q = max(n, max(m, nmsl));
    fac[0] = 1;
    for (int i = 1; i <= q; ++i)
        fac[i] = fac[i - 1] * i % mod;
    inv[q] = quickpow(fac[q]);
    for (int i = q - 1; i >= 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % mod;

    for (int i = 1; i <= nmsl; ++i)
    {
        f[i] = (quickpow(i, n) - quickpow(i - 1, n)) * (quickpow(i, m) - quickpow(i - 1, m)) % mod;
        f[i] = (f[i] + mod) % mod;
    }
    for (int i = 1; i <= nmsl; ++i)
        (f[i] += f[i - 1]) %= mod;
    printf("%lld\n", lagrange(k, nmsl));
    return 0;
}
