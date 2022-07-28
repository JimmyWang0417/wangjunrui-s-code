/**
 *    unicode: UTF-8
 *    name:    P5323 [BJOI2019]光线
 *    author:  wangjunrui
 *    created: 2022.07.21 周四 10:32:54 (Asia/Shanghai)
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
constexpr int N = 5e5 + 5;
constexpr int mod = 1e9 + 7;
constexpr inline ll quickpow(ll a, int b)
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
constexpr int inv100 = quickpow(100, mod - 2);
int n;
signed main()
{
    read(n);
    ll p = 1, q = 0;
    for (int i = 1; i <= n; ++i)
    {
        ll a, b;
        read(a, b);
        (a *= inv100) %= mod;
        (b *= inv100) %= mod;
        ll qwq = quickpow(1 - q * b % mod, mod - 2);
        p = p * a % mod * qwq % mod;
        q = b + q * a % mod * a % mod * qwq % mod;
    }
    printf("%lld\n", (p + mod) % mod);
    return 0;
}