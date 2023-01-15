/**
 *    unicode: UTF-8
 *    name:    CF1418G Three Occurrences
 *    author:  whitepaperdog
 *    created: 2022.08.01 周一 20:24:17 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <vector>
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
constexpr int N = 1e5 + 5;
int n, m;
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
int where[N], p[N * 2], tot;
int dfn[N], rk[N], dfstime;
int dep[N];
int dp[N * 2][25], Log[N * 2];
int fa[N];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[fa[u] = _fa] + 1;
    rk[dfn[u] = ++dfstime] = u;
    p[where[u] = ++tot] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        p[++tot] = u;
    }
}
inline int calc(int x, int y)
{
    return dep[x] < dep[y] ? x : y;
}
inline int getlca(int x, int y)
{
    x = where[x], y = where[y];
    if (x > y)
        swap(x, y);
    int k = Log[y - x + 1];
    return calc(dp[x][k], dp[y - (1 << k) + 1][k]);
}
struct Tree
{
    int l, r;
    int size;
    int lc, rc, ans;
} tree[N * 50];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline void pushup(int rt)
{
    tree[rt].ans = tree[lc(rt)].ans + tree[rc(rt)].ans;
    if (tree[lc(rt)].rc && tree[rc(rt)].lc)
        tree[rt].ans -= dep[getlca(rk[tree[lc(rt)].rc], rk[tree[rc(rt)].lc])];
    tree[rt].lc = tree[lc(rt)].lc ? tree[lc(rt)].lc : tree[rc(rt)].lc;
    tree[rt].rc = tree[rc(rt)].rc ? tree[rc(rt)].rc : tree[lc(rt)].rc;
}
inline void update(int &rt, int l, int r, int pos, int val)
{
    if (!rt)
        rt = ++cnt;
    if (l == r)
    {
        tree[rt].size += val;
        if (tree[rt].size)
        {
            tree[rt].lc = tree[rt].rc = l;
            tree[rt].ans = dep[rk[l]];
        }
        else
            tree[rt].ans = tree[rt].lc = tree[rt].rc = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val);
    else
        update(rc(rt), mid + 1, r, pos, val);
    pushup(rt);
}
inline void merge(int &x, int y, int l, int r)
{
    if (!x || !y)
    {
        x = x | y;
        return;
    }
    if (l == r)
    {
        tree[x].size += tree[y].size;
        if (tree[x].size)
        {
            tree[x].lc = tree[x].rc = l;
            tree[x].ans = dep[rk[l]];
        }
        else
            tree[x].ans = tree[x].lc = tree[x].rc = 0;
        return;
    }
    int mid = (l + r) >> 1;
    merge(lc(x), lc(y), l, mid);
    merge(rc(x), rc(y), mid + 1, r);
    pushup(x);
}
vector<int> g[N], h[N];
inline int query(int rt)
{
    if (!rt)
        return 0;
    return tree[rt].ans - dep[getlca(rk[tree[rt].lc], rk[tree[rt].rc])];
}
ll answer;
inline void solve(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        solve(v, u);
        merge(root[u], root[v], 1, n);
    }
    for (int v : g[u])
        update(root[u], 1, n, dfn[v], 1);
    for (int v : h[u])
        update(root[u], 1, n, dfn[v], -1);
    answer += query(root[u]);
}
signed main()
{
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    Log[0] = -1;
    for (int i = 1; i <= tot; ++i)
    {
        Log[i] = Log[i >> 1] + 1;
        dp[i][0] = p[i];
    }
    for (int j = 1; j <= Log[tot]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= tot; ++i)
            dp[i][j] = calc(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(u);
        g[u].push_back(v);
        g[v].push_back(u);
        g[v].push_back(v);
        int lca = getlca(u, v);
        h[lca].push_back(u);
        h[lca].push_back(v);
        h[fa[lca]].push_back(u);
        h[fa[lca]].push_back(v);
    }
    solve(1, 0);
    printf("%lld\n", answer >> 1);
    return 0;
}