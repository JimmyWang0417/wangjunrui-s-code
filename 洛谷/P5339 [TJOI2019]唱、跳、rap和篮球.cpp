/**
 *    unicode: UTF-8
 *    name:    P5339 [TJOI2019]唱、跳、rap和篮球
 *    author:  wangjunrui
 *    created: 2022.07.26 周二 08:44:49 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1005;
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
ll fac[N], ifac[N];
inline ll C(int x, int y)
{
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
int n, a, b, c, d;
ll f[N], g[N];
signed main()
{
    read(n, a, b, c, d);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    ll ans = 0;
    for (int i = min(a, min(a, min(c, min(d, n / 4)))); i >= 0; --i)
    {
        int limit = n - 4 * i;
        f[0] = 1;
        copy(f, f + 1 + limit, g);
        fill(f, f + 1 + limit, 0);
        for (int j = 0; j <= limit; ++j)
            if (g[j])
                for (int k = 0; i + k <= a && j + k <= limit; ++k)
                    (f[j + k] += g[j] * ifac[k]) %= mod;
        copy(f, f + 1 + limit, g);
        fill(f, f + 1 + limit, 0);
        for (int j = 0; j <= limit; ++j)
            if (g[j])
                for (int k = 0; i + k <= b && j + k <= limit; ++k)
                    (f[j + k] += g[j] * ifac[k]) %= mod;
        copy(f, f + 1 + limit, g);
        fill(f, f + 1 + limit, 0);
        for (int j = 0; j <= limit; ++j)
            if (g[j])
                for (int k = 0; i + k <= c && j + k <= limit; ++k)
                    (f[j + k] += g[j] * ifac[k]) %= mod;
        copy(f, f + 1 + limit, g);
        fill(f, f + 1 + limit, 0);
        for (int j = 0; j <= limit; ++j)
            if (g[j])
                for (int k = 0; i + k <= d && j + k <= limit; ++k)
                    (f[j + k] += g[j] * ifac[k]) %= mod;
        (ans += (i & 1 ? -1 : 1) * C(n - 3 * i, i) * f[limit] % mod * fac[n - 4 * i]) %= mod;
        fill(f, f + 1 + limit, 0);
    }
    printf("%lld\n", ans);
    return 0;
}