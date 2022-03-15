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
const int N = 1e6 + 5;
const int mod = 998244353;
inline ll quickpow(ll a, ll b)
{
    if (b == 0)
        return 1;
    else if (b < 0)
        return quickpow(quickpow(a, -b), mod - 2);
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
#define calc(x) (((x)&1) ? -1 : 1)
int n;
signed main()
{
    read(n);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    inv[n] = quickpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        (ans += C(n, i) * quickpow(3, -(ll)i * n) % mod * calc(i) * (quickpow((1 - quickpow(3, -n + i)), n) - 1)) %= mod;
    ans = -ans * quickpow(3, (ll)n * n + 1) % mod;
    ll res = 0;
    for (int i = 1; i <= n; ++i)
        (res += C(n, i) * calc(i + 1) * quickpow(3, i) % mod * quickpow(3, (ll)n * (n - i))) %= mod;
    printf("%lld\n", ((2 * res + ans) % mod + mod) % mod);
    return 0;
}