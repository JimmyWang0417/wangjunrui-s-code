/**
 *    unicode: UTF-8
 *    name:    AT3965 [AGC025B] RGB Coloring
 *    author:  whitepaperdog
 *    created: 2022.07.31 周日 20:26:05 (Asia/Shanghai)
 **/
#include <cstdio>
#define int ll
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
constexpr int N = 3e5 + 5;
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
int n, A, B;
ll m;
ll fac[N], ifac[N];
inline ll C(int _x, int _y)
{
    if (_x < _y || _y < 0)
        return 0;
    return fac[_x] * ifac[_y] % mod * ifac[_x - _y] % mod;
}
signed main()
{
    read(n, A, B, m);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    ll res = 0;
    for (int i = 0; i <= n; ++i)
    {
        if (i * A > m)
            break;
        if ((m - i * A) % B == 0)
            (res += C(n, i) * C(n, (m - i * A) / B)) %= mod;
    }
    printf("%lld\n", res);
    return 0;
}