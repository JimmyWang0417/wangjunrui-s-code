#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 2005;
const int mod = 1e9 + 7;
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
int k;
ll a, b;
ll dp[N][N];
signed main()
{
    read(k, a, b);
    ll inv = quickpow(a + b, mod - 2);
    (a *= inv) %= mod, (b *= inv) %= mod;
    inv = quickpow(1 - a, mod - 2);
    ll add = a * b % mod * inv % mod * inv % mod;
    dp[1][0] = 1;
    for (int i = 1; i < k; ++i)
        for (int j = 0; i + j < k; ++j)
        {
            (dp[i + 1][j] += dp[i][j] * a) %= mod;
            (dp[i][i + j] += dp[i][j] * b) %= mod;
        }
    ll ans = 0;
    for (int i = 1; i <= k; ++i)
        for (int j = k - i; j < (k << 1); ++j)
            (ans += dp[i][j] * (i + j + add)) %= mod;
    printf("%lld\n", ans);
    return 0;
}