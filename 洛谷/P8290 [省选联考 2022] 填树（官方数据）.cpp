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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 205;
constexpr int mod = 1e9 + 7, inv2 = (mod + 1) / 2;
int n, k;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
struct node
{
    int l, r;
} a[N];
int p[N * 10], tot;
ll dp[N], f[N], g[N], h[N];
bool vis[N];
inline void dfs(int u, int _fa, int l, int r)
{
    vis[u] = true;
    int x = max(l, a[u].l), y = min(r, a[u].r);
    dp[u] = f[u] = 0;
    if (x > y)
        return;
    dp[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u, l, r);
        (dp[u] += dp[v]) %= mod;
        (f[u] += (y - x + 1) * f[v]) %= mod;
    }
    (dp[u] *= (y - x + 1)) %= mod;
    (f[u] += (dp[u] * (y + x) % mod * inv2)) %= mod;
}
inline void solve(int u, int _fa, int l, int r)
{
    g[u] = dp[u], h[u] = f[u];
    int x = max(l, a[u].l), y = min(r, a[u].r);
    if (x > y)
        return;
    if (_fa)
    {
        x = max(l, a[_fa].l), y = min(r, a[_fa].r);
        ll addg = (g[_fa] - dp[u] * (y - x + 1)) % mod;
        ll addh = (h[_fa] - (y - x + 1) * f[u] - dp[u] * (y - x + 1) % mod * (y + x) % mod * inv2) % mod;
        x = max(l, a[u].l), y = min(r, a[u].r);
        (g[u] += addg * (y - x + 1)) %= mod;
        (h[u] += (y - x + 1) * addh + addg * (y - x + 1) % mod * (y + x) % mod * inv2) %= mod;
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        solve(v, u, l, r);
    }
}
inline pair<ll, ll> solve(int l, int r)
{
    ll res = 0, now = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (!vis[i])
        {
            dfs(i, 0, l, r);
            solve(i, 0, l, r);
        }
        (res += g[i]) %= mod;
        (now += h[i]) %= mod;
    }
    memset(vis, 0, sizeof(vis));
    return make_pair(res, now);
}
int m, Y[N];
ll pre[N], suf[N];
ll fac[N], ifac[N];
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
inline ll lagrange(int x)
{
    pre[0] = 1;
    for (int i = 1; i <= m; ++i)
        pre[i] = pre[i - 1] * (x - i) % mod;
    suf[m + 1] = 1;
    for (int i = m; i >= 1; --i)
        suf[i] = suf[i + 1] * (x - i) % mod;
    ll ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        ll a = pre[i - 1] * suf[i + 1] % mod, b = fac[i - 1] * fac[m - i] % mod * ((m - i) & 1 ? -1 : 1);
        (ans += Y[i] * a % mod * quickpow(b, mod - 2) % mod) %= mod;
    }
    return (ans + mod) % mod;
}
int dep[N], root;
inline void dfs1(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
    }
    if (dep[u] > dep[root])
        root = u;
}
ll b[N], c[N];
signed main()
{
    read(n, k);
    fac[0] = 1;
    for (int i = 1; i <= 200; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[200] = quickpow(fac[200], mod - 2);
    for (int i = 200 - 1; i >= 0; --i)
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].l, a[i].r);
        p[++tot] = a[i].l - k;
        p[++tot] = a[i].l;
        p[++tot] = a[i].r - k;
        p[++tot] = a[i].r;
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    p[tot + 1] = p[tot] + 1;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    dfs1(root, 0);
    int maxx = dep[root];
    ll ans = 0, sum = 0;
    for (int kase = 1; kase <= tot; ++kase)
    {
        m = min(maxx + 1, p[kase + 1] - p[kase]);
        for (int i = 1; i <= m; ++i)
        {
            pair<ll, ll> tmp = solve(p[kase] + i - 1, p[kase] + i - 1 + k);
            b[i] = (b[i - 1] + tmp.first) % mod, c[i] = (c[i - 1] + tmp.second) % mod;
            tmp = solve(p[kase] + i, p[kase] + i - 1 + k);
            (b[i] -= tmp.first) %= mod, (c[i] -= tmp.second) %= mod;
            for (int u = 1; u <= n; ++u)
                if (a[u].l <= p[kase] + i - 1 && p[kase] + i - 1 <= a[u].r)
                {
                    (++b[i]) %= mod;
                    (c[i] += p[kase] + i - 1) %= mod;
                }
        }
        for (int i = 1; i <= m; ++i)
            Y[i] = b[i];
        (ans += lagrange(p[kase + 1] - p[kase]) * inv2) %= mod;
        for (int i = 1; i <= m; ++i)
            Y[i] = c[i];
        (sum += lagrange(p[kase + 1] - p[kase]) * inv2) %= mod;
    }
    printf("%lld\n%lld\n", (ans + mod) % mod, (sum + mod) % mod);
    return 0;
}