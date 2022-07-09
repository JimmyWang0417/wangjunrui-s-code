/**
 *    unicode: UTF-8
 *    name:    P5395 第二类斯特林数·行
 *    author:  wangjunrui
 *    created: 2022.07.04 周一 23:35:00 (Asia/Shanghai)
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
constexpr int N = 1e6 + 5;
constexpr int mod = 167772161;
constexpr int inv3 = 55924054;
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
int n;
ll fac[N], ifac[N];
int limit, len, rk[N];
ll A[N], B[N];
inline void init(int all)
{
    len = 0, limit = 1;
    while (limit <= all)
    {
        limit <<= 1;
        ++len;
    }
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
}
inline void NTT(ll *dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(3, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += mid << 1)
        {
            ll g = 1;
            for (int i = 0; i < mid; ++i, (g *= gn) %= mod)
            {
                ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
                dp[i + j] = (x + y) % mod;
                dp[i + j + mid] = (x - y) % mod;
            }
        }
    }
}
inline void INTT(ll *dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(inv3, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += mid << 1)
        {
            ll g = 1;
            for (int i = 0; i < mid; ++i, (g *= gn) %= mod)
            {
                ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
                dp[i + j] = (x + y) % mod;
                dp[i + j + mid] = (x - y) % mod;
            }
        }
    }
    ll inv = quickpow(limit, mod - 2);
    for (int i = 0; i < limit; ++i)
        (dp[i] *= inv) %= mod;
}
signed main()
{
    read(n);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    for (int i = 0; i <= n; ++i)
    {
        A[i] = quickpow(i, n) * ifac[i] % mod;
        B[i] = (i & 1 ? -1 : 1) * ifac[i];
    }
    init(n * 2);
    NTT(A), NTT(B);
    for (int i = 0; i < limit; ++i)
        (A[i] *= B[i]) %= mod;
    INTT(A);
    for (int i = 0; i <= n; ++i)
        printf("%lld ", (A[i] + mod) % mod);
    putchar('\n');
    return 0;
}