/**
 *    unicode: UTF-8
 *    name:    CF1437F Emotional Fishermen
 *    author:  wangjunrui
 *    created: 2022.07.02 周六 22:27:16 (Asia/Shanghai)
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
constexpr int N = 5005;
constexpr int mod = 998244353;
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
int n, a[N], b[N];
ll dp[N], sum[N];
ll fac[N], ifac[N];
signed main()
{
    read(n);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    sort(a + 1, a + 1 + n);
    if (a[n] < a[n - 1] * 2)
    {
        puts("0");
        return 0;
    }
    dp[0] = 1;
    sum[0] = fac[n - 1];
    for (int i = 1, j = 0; i <= n; ++i)
    {
        while (a[i] >= a[j] * 2)
            ++j;
        dp[i] = ifac[n - j] * sum[j - 1] % mod;
        sum[i] = (sum[i - 1] + dp[i] * fac[n - j - 1]) % mod;
    }
    printf("%lld\n", dp[n]);
    return 0;
}