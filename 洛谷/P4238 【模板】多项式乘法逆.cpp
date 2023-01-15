/**
 *    unicode: UTF-8
 *    name:    P4238 【模板】多项式乘法逆
 *    author:  whitepaperdog
 *    created: 2022.08.18 周四 20:01:35 (Asia/Shanghai)
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
constexpr int N = (1 << (__lg((int)1e5 - 1) + 1)) * 2 + 1;
constexpr int mod = 998244353;
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
constexpr int inv3 = quickpow(3, mod - 2);
int limit, rk[N];
inline void init(int all)
{
    limit = 1;
    while (limit <= all)
        limit <<= 1;
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) ? limit >> 1 : 0);
}
inline void NTT(ll *dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(3, (mod - 1) / (mid << 1));
        for (int i = 0; i < limit; i += (mid << 1))
        {
            ll g = 1;
            for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
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
        for (int i = 0; i < limit; i += (mid << 1))
        {
            ll g = 1;
            for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
            {
                ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
                dp[i + j] = (x + y) % mod;
                dp[i + j + mid] = (x - y) % mod;
            }
        }
    }
    ll invlimit = quickpow(limit, mod - 2);
    for (int i = 0; i < limit; ++i)
        (dp[i] *= invlimit) %= mod;
}
int A[N];
ll F[N], G[N];
inline void solve(int n)
{
    if (n == 1)
    {
        F[0] = quickpow(A[0], mod - 2);
        return;
    }
    solve((n + 1) / 2);
    init(n * 2);
    copy(A, A + n, G);
    fill(G + n, G + limit, 0);
    NTT(F), NTT(G);
    for (int i = 0; i < limit; ++i)
        F[i] = (2 - F[i] * G[i]) % mod * F[i] % mod;
    INTT(F);
    fill(F + n, F + limit, 0);
}
signed main()
{
    int n;
    read(n);
    for (int i = 0; i < n; ++i)
        read(A[i]);
    solve(n);
    for (int i = 0; i < n; ++i)
        printf("%lld ", (F[i] + mod) % mod);
    putchar('\n');
    return 0;
}