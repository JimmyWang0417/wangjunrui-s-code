/**
 *    unicode: UTF-8
 *    name:    P5408 第一类斯特林数·行
 *    author:  whitepaperdog
 *    created: 2022.07.03 周日 21:23:22 (Asia/Shanghai)
 **/
#include <algorithm>
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
ll fac[N], ifac[N];
inline ll C(int n, int m)
{
    return fac[n] * fac[m] % mod * fac[n - m] % mod;
}
ll A[N], B[N];
int len, limit, rk[N];
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
ll answer[N];
inline void solve(int n)
{
    if (n == 1)
    {
        answer[1] = 1;
        return;
    }
    int las = n / 2;
    solve(las);
    for (int i = 0; i <= las; ++i)
        A[las - i] = answer[i] * fac[i] % mod;
    ll power = 1;
    for (int i = 0; i <= las; ++i, (power *= las) %= mod)
        B[i] = power * ifac[i] % mod;
    init(las * 2);
    NTT(A), NTT(B);
    for (int i = 0; i < limit; ++i)
        (A[i] *= B[i]) %= mod;
    INTT(A);
    reverse(A, A + las + 1);
    for (int i = 0; i <= las; ++i)
        (A[i] *= ifac[i]) %= mod;
    fill(A + las + 1, A + limit, 0);
    fill(B + 0, B + limit, 0);
    init(n);
    NTT(answer), NTT(A);
    for (int i = 0; i < limit; ++i)
        (answer[i] *= A[i]) %= mod;
    INTT(answer);
    fill(A + 0, A + limit, 0);
    if (n & 1)
        for (int i = n; i >= 1; --i)
            answer[i] = (answer[i - 1] + (n - 1) * answer[i]) % mod;
}
signed main()
{
    int n;
    read(n);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    if(n)
        solve(n);
    else
        answer[0] = 1;
    for (int i = 0; i <= n; ++i)
        printf("%lld ", (answer[i] + mod) % mod);
    putchar('\n');
    return 0;
}