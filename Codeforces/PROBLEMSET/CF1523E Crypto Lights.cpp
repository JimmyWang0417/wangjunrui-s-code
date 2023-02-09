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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
constexpr int limit = 1e5;
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
ll fac[N], ifac[N];
inline ll C(int x, int y)
{
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
int n, m;
signed main()
{
    fac[0] = 1;
    for (int i = 1; i <= limit; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[limit] = quickpow(fac[limit]);
    for (int i = limit; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    int T = 1;
    read(T);
    while (T--)
    {
        read(n, m);
        ll res = 1;
        for (int i = 1; i <= n && n - (i - 1) * (m - 1) >= i; ++i)
            (res += C(n - (i - 1) * (m - 1), i) * quickpow(C(n, i))) %= mod;
        printf("%lld\n", res);
    }
    return 0;
}