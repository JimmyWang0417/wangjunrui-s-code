#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
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
constexpr int mod = 998244353;
constexpr int mod2 = 3 << 27;
int prime[N], tot;
int phi[N], mul[N];
bool vis[N];
ll inv[N];
ll dp[N];
inline ll quickpow(ll a, ll b = mod - 2, int p = mod)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}
inline void init(int n)
{
    phi[1] = mul[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            mul[i] = -1;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                mul[i * prime[j]] = 0;
                break;
            }
            else
                mul[i * prime[j]] = -mul[i];
        }
    }
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 0; i <= n; ++i)
        dp[i] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; i * j <= n; ++j)
            if (mul[j] == 1)
                (dp[i * j] *= i) %= mod;
            else if (mul[j] == -1)
                (dp[i * j] *= inv[i]) %= mod;
    }
    for (int i = 1; i <= n; ++i)
        (dp[i] *= dp[i - 1]) %= mod;
}
int n;
ll power[10];
char str[N];
ll m;
signed main()
{
    init(1e6);
    int T;
    read(T);
    while (T--)
    {
        read(n);
        scanf("%s", str + 1);
        m = 0;
        for (int i = 1; str[i]; ++i)
            m = (m * 10 + str[i] - '0') % mod2;
        ll ans = 1;
        for (int l = 1, r; l <= n; l = r + 1)
        {
            r = n / (n / l);
            ll res = quickpow(n, m, mod - 1) - quickpow(n - n / l, m, mod - 1);
            if (res < 0)
                res += mod - 1;
            (ans *= quickpow(dp[r] * quickpow(dp[l - 1]) % mod, res)) %= mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}