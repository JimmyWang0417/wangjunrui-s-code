#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>
#include <list>
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
constexpr ll INF = 1e18;
int n, m, S, T;
struct Edge
{
    int next, to, dis;
} edge[N * 4];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
ll dis[N];
int pre[N];
bool vis[N];
inline void dijkstra()
{
    memset(dis, 0x3f, sizeof(dis));
    __gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>> q;
    memset(vis, 0, sizeof(vis));
    q.push(make_pair(dis[T] = 0, T));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
            {
                pre[v] = u;
                q.push(make_pair(dis[v] = dis[u] + edge[i].dis, v));
            }
        }
    }
}
list<int> g[N];
int size[N], son[N];
int dep[N], fa[N];
inline void dfs1(int u, int _fa)
{
    dep[u] = dep[fa[u] = _fa] + 1;
    size[u] = 1;
    for (auto v : g[u])
    {
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
int dfn[N], dfstime, rk[N];
int top[N];
inline void dfs2(int u, int topf)
{
    top[u] = topf;
    rk[dfn[u] = ++dfstime] = u;
    if (son[u])
        dfs2(son[u], topf);
    for (auto v : g[u])
    {
        if (top[v])
            continue;
        dfs2(v, v);
    }
}
struct Tree
{
    ll min, tag;
    inline void update(ll val)
    {
        ckmin(min, val);
        ckmin(tag, val);
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].min = min(tree[lc].min, tree[rc].min);
}
inline void pushdown(int rt)
{
    if (tree[rt].tag == INF)
        return;
    tree[lc].update(tree[rt].tag);
    tree[rc].update(tree[rt].tag);
    tree[rt].tag = INF;
}
inline void build(int rt, int l, int r)
{
    tree[rt].min = tree[rt].tag = INF;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int x, int y, ll val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline void update(int x, int y, ll val)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(1, 1, n, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(1, 1, n, dfn[x] + 1, dfn[y], val);
}
ll dp[N];
inline void solve(int rt, int l, int r)
{
    if (l == r)
    {
        dp[rk[l]] = tree[rt].min - dis[rk[l]];
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    solve(lc, l, mid);
    solve(rc, mid + 1, r);
}
inline void work()
{
    memset(dis, 0x3f, sizeof(dis));
    __gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>> q;
    memset(vis, 0, sizeof(vis));
    q.push(make_pair(dis[T] = 0, T));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > max(dis[u] + edge[i].dis, dp[v]))
            {
                pre[v] = u;
                q.push(make_pair(dis[v] = max(dis[u] + edge[i].dis, dp[v]), v));
            }
        }
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
#endif
    read(n, m, S, T);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dijkstra();
    for (int i = 1; i <= n; ++i)
        if (pre[i])
            g[pre[i]].push_back(i);
    dfs1(T, 0);
    dfs2(T, T);
    build(1, 1, n);
    for (int i = 2; i <= num_edge; i += 2)
    {
        int u = edge[i].to, v = edge[i ^ 1].to;
        if (pre[u] == v || pre[v] == u)
            continue;
        update(u, v, dis[u] + edge[i].dis + dis[v]);
    }
    solve(1, 1, n);
    work();
    if (dis[S] >= INF / 2)
        printf("-1\n");
    else
        printf("%lld\n", dis[S]);
    return 0;
}
