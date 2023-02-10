#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 4e5 + 5;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int next, to, dis;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int dis[N];
bool vis[N];
int pre[N];
int fa[N][25];
inline void dijkstra()
{
    memset(dis, INF, sizeof(dis));
    dis[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(0, 1));

    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
            {
                pre[v] = u;
                dis[v] = dis[u] + edge[i].dis;
                q.push(make_pair(dis[v], v));
            }
        }
    }
}
int n, m;
vector<int> g[N];
int dep[N];
inline void init(int u)
{
    dep[u] = dep[pre[u]] + 1;
    fa[u][0] = pre[u];
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (auto v : g[u])
        init(v);
}
inline int LCA(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
struct Tree
{
    int l, r;
    int val;
    int dist;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt, root[N];
inline int newnode(int val)
{
    int now = ++cnt;
    tree[now].dist = 0;
    lc(now) = rc(now) = 0;
    tree[now].val = val;
    tree[now].dist = 1;
    return now;
}
inline int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    if (tree[x].val > tree[y].val)
        swap(x, y);
    rc(x) = merge(rc(x), y);
    if (tree[lc(x)].dist < tree[rc(x)].dist)
        swap(lc(x), rc(x));
    tree[x].dist = tree[rc(x)].dist + 1;
    return x;
}
vector<int> del[N];
int ans[N];
inline void dfs(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (pre[v] != u && pre[u] != v)
        {
            int now = newnode(dis[u] + dis[v] + edge[i].dis);
            root[u] = merge(root[u], now);
            del[LCA(u, v)].push_back(now);
        }
    }
    for (auto v : g[u])
    {
        dfs(v);
        root[u] = merge(root[u], root[v]);
    }
    for (auto v : del[u])
        vis[v] = true;
    while (root[u] && vis[root[u]])
        root[u] = merge(lc(root[u]), rc(root[u]));
    if (root[u])
        ans[u] = tree[root[u]].val - dis[u];
}
signed main()
{
    freopen("pal.in", "r", stdin), freopen("pal.out", "w", stdout);
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dijkstra();
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= n; ++i)
        g[pre[i]].push_back(i);
    init(1);
    for (int i = 1; i <= n; ++i)
        ans[i] = -1;
    dfs(1);
    for (int i = 2; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
