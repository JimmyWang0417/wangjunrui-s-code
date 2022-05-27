#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 2e5 + 5;
const int mod = 998244353;
const int inv2 = (mod + 1) / 2;
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
ll fac[N], inv[N];
inline ll C(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int n, m, k, a[N];
signed main()
{
    read(n, k);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        m += (a[i] != a[i % n + 1]);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    inv[n] = quickpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    if (k == 1)
    {
        printf("0\n");
        return 0;
    }
    else if (k == 2)
    {
        ll ans = 0;
        for (int i = 1; i <= m; ++i)
            (ans += C(m, i) * (i > m - i)) %= mod;
        printf("%lld\n", ans * quickpow(k, n - m) % mod);
    }
    else
    {
        ll ans = 0;
        for (int i = 0; i * 2 <= m; ++i)
            (ans += C(m, i) * C(m - i, i) % mod * quickpow(k - 2, m - 2 * i) % mod) %= mod;
        printf("%lld\n", (quickpow(k, n) - ans * quickpow(k, n - m) % mod + mod) % mod * inv2 % mod);
    }
    return 0;
}