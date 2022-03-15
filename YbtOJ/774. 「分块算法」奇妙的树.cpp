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
constexpr int N = 2.5e5 + 5;
constexpr int mod = 998244353;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
template <typename T>
inline void dec(T &x, T y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n, q;
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int a[N], fa[N];
int size[N], son[N];
int dep[N];
inline void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1;
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs1(v);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
}
int dfn[N], dfstime, id[N];
int top[N], tftft[N];
inline void dfs2(int u, int topf)
{
    id[dfn[u] = ++dfstime] = u;
    top[u] = topf;
    tftft[u] = top[fa[top[fa[top[u]]]]];
    if (son[u])
        dfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (top[v])
            continue;
        dfs2(v, v);
    }
}
inline int calc(int u, int depf)
{
    if (dep[u] <= depf)
        return u;
    while (dep[tftft[u]] > depf)
        u = fa[tftft[u]];
    while (dep[top[u]] > depf)
        u = fa[top[u]];
    return id[dfn[top[u]] + depf - dep[top[u]]];
}
int block, num;
int L[N], R[N], belong[N];
int g[N];
int sum[500][N];
int sum2[500][N];
inline void dfs(int u, int *dp)
{
    dp[u] = a[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v, dp);
        add(dp[u], dp[v]);
    }
}
ll answer, f[N];
int c[N];
signed main()
{
    freopen("slight.in", "r", stdin), freopen("slight.out", "w", stdout);
    read(n, q);
    block = (int)(1.2 * sqrt(n));
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 2; i <= n; ++i)
        read(fa[i]);
    for (int i = 1, j = 1; i <= n; ++i)
    {
        while (fa[j] < i)
            ++j;
        g[i] = j - 1;
        add_edge(fa[i], i);
        if (i % block == 0)
        {
            answer = 0;
            dfs(1, sum[belong[i]]);
            for (int k = 1; k <= i; ++k)
                sum2[belong[i]][k] = (int)(((ll)sum[belong[i]][k] * sum[belong[i]][k] + sum2[belong[i]][k - 1]) % mod);
        }
    }
    dfs1(1);
    dfs2(1, 1);
    int lastans = 0;
    memset(c, -1, sizeof(c));
    while (q--)
    {
        int l, r;
        read(l, r);
        l ^= lastans, r ^= lastans;
        int bel = belong[r], maxx = R[bel - 1];
        int ans = 0;
        if (l <= maxx)
        {
            ans = sum2[bel - 1][min(g[l], maxx)];
            dec(ans, sum2[bel - 1][min(maxx, l - 1)]);
        }
        for (int i = max(l, maxx + 1); i <= r; ++i)
        {
            int x = calc(i, dep[l] + 1);
            if (x > g[l])
                x = fa[x];
            if (c[x] == -1)
            {
                c[x] = (x <= maxx ? sum[bel - 1][x] : 0);
            }
            add(ans, (int)((2ll * c[x] * a[i] + (ll)a[i] * a[i]) % mod));
            add(c[x], a[i]);
        }
        printf("%d\n", lastans = ans);
        for (int i = max(l, maxx + 1); i <= r; ++i)
        {
            int x = calc(i, dep[l] + 1);
            if (x > g[l])
                x = fa[x];
            c[x] = -1;
        }
    }
    return 0;
}
