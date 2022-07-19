/**
 *    unicode: UTF-8
 *    name:    LadiesCF286E Ladies' Shop
 *    author:  wangjunrui
 *    created: 2022.07.11 周一 21:08:16 (Asia/Shanghai)
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
constexpr int N = 4e6 + 6;
constexpr int mod = 998244353;
constexpr int inv3 = (mod + 1) / 3;
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
int n, m, a[N];
ll A[N];
int mp[N];
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
    ll inv = quickpow(limit, mod - 2);
    for (int i = 0; i < limit; ++i)
        (dp[i] *= inv) %= mod;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        A[a[i]] = mp[a[i]] = 1;
    }
    init(m * 2);
    NTT(A);
    for (int i = 0; i < limit; ++i)
        (A[i] *= A[i]) %= mod;
    INTT(A);
    for (int i = 1; i <= m; ++i)
        if (!mp[i] && A[i])
        {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");
    int res = 0;
    for (int i = 1; i <= m; ++i)
        if (mp[i] && !A[i])
            ++res;
    printf("%d\n", res);
    for (int i = 1; i <= m; ++i)
        if (mp[i] && !A[i])
            printf("%d ", i);
    putchar('\n');
    return 0;
}