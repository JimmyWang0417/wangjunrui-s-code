/**
 *    unicode: UTF-8
 *    name:    P8367 [LNOI2022] 盒
 *    author:  whitepaperdogdogdog (蒟蒻wjr)
 *    located: Changle District, Fuzhou City, Fujian Province, China
 *    created: 2022.08.27 周六 19:56:46 (Asia/Shanghai)
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
constexpr int N = 5e5 + 5, M = 2e6 + 5;
constexpr int mod = 998244353;
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
int n, m, a[N], b[N];
ll fac[N + M], ifac[N + M];
inline ll C(int _n, int _m)
{
    if (_n < 0 || _n < _m)
        return 0;
    return fac[_n] * ifac[_m] % mod * ifac[_n - _m] % mod;
}
namespace calculate
{
    int l, r;
    ll res;
    inline ll _f(int n, int m, int _l, int _r)
    {
        l = _l, r = _r;
        res = 0;
        for (int i = 0; i <= r; ++i)
            (res += C(l + i - 1, l - 1) * C(n - l + m - i - 1, n - l - 1)) %= mod;
        return res;
    }
    inline void init(int n, int m, int _l, int _r)
    {
        l = _l, r = _r;
        res = _f(n, m, _l, _r);
    }
    inline ll f(int n, int m, int _l, int _r)
    {
        while (r < _r)
        {
            ++r;
            (res += C(l + r - 1, l - 1) * C(n - l + m - r - 1, n - l - 1)) %= mod;
        }
        while (l < _l)
        {
            ++l;
            (res -= C(l + r - 1, l - 1) * C(n - l + m - r - 1, n - l)) %= mod;
        }
        return res;
    }
    inline ll g(int n, int m, int _l, int _r)
    {
        return _l * f(n + 1, m - 1, _l + 1, _r - 1) % mod;
    }
}
signed main()
{
    m = N + M - 10;
    fac[0] = 1;
    for (int i = 1; i <= m; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[m] = quickpow(fac[m], mod - 2);
    for (int i = m; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    int T = 1;
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)
        {
            read(a[i]);
            a[i] += a[i - 1];
        }
        for (int i = 1; i < n; ++i)
            read(b[i]);
        m = a[n];
        ll res = 0;
        calculate::init(n, m, 1, a[1]);
        for (int i = 1; i < n; ++i)
            (res += (ll)a[i] * b[i] % mod * calculate::f(n, m, i, a[i]) % mod) %= mod;
        calculate::init(n + 1, m - 1, 2, a[1] - 1);
        for (int i = 1; i < n; ++i)
            (res -= b[i] * calculate::g(n, m, i, a[i])) %= mod;
        (res *= 2) %= mod;
        for (int i = 1; i < n; ++i)
            (res += (i * C(n + m - 1, n) - a[i] * C(n + m - 1, m)) % mod * b[i]) %= mod;
        printf("%lld\n", (res + mod) % mod);
    }
    return 0;
}