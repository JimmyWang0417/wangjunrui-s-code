#include <bits/extc++.h>
#include <bits/stdc++.h>
#define int ll
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
constexpr int N = 1e5 + 5;
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
int n, m, a[N];
vector<int> g[N];
ll dp[N];
ll f[N], h[N], inv[N];
inline void dfs1(int u, int _fa)
{
    dp[u] = a[u];
    if (g[u].size() == 1)
    {
        f[u] = 0;
        inv[u] = 1;
        return;
    }
    f[u] = quickpow(g[u].size(), mod - 2);
    ll res = 0;
    for (auto v : g[u])
    {
        if (v == _fa)
            continue;
        dfs1(v, u);
        (res += f[v]) %= mod;
        (dp[u] += f[u] * dp[v]) %= mod;
    }
    inv[u] = quickpow((1 - res * f[u] % mod + mod) % mod, mod - 2);
    (dp[u] *= inv[u]) %= mod;
    (f[u] *= inv[u]) %= mod;
}
inline void dfs2(int u, int _fa, ll res = 1)
{
    h[u] = inv[u] * res % mod;
    ll mul = res * f[u] % mod;
    for (auto v : g[u])
    {
        if (v == _fa)
            continue;
        dfs2(v, u, mul);
    }
}
signed main()
{
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    ll res = dp[1];
    printf("%lld\n", (res + mod) % mod);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        (res += h[x] * (y - a[x])) %= mod;
        a[x] = y;
        printf("%lld\n", (res + mod) % mod);
    }
    return 0;
}
