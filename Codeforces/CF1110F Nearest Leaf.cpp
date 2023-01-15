/**
 *    unicode: UTF-8
 *    name:    CF1110F Nearest Leaf
 *    author:  whitepaperdog
 *    created: 2022.07.07 周四 00:52:33 (Asia/Shanghai)
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
constexpr int N = 5e5 + 5;
int n, m;
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
struct Tree
{
    ll tag, min;
    inline void update(ll val)
    {
        tag += val;
        min += val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
ll dis[N];
inline void pushup(int rt)
{
    tree[rt].min = min(tree[lc].min, tree[rc].min);
}
inline void pushdown(int rt)
{
    if (tree[rt].tag)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].min = head[l] ? (ll)1e18 : dis[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y, int val)
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
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 1e18;
    if (x <= l && r <= y)
        return tree[rt].min;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return min(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
int dp[N];
inline void dfs(int u)
{
    dp[u] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dis[v] = dis[u] + edge[i].dis;
        dfs(v);
        ckmax(dp[u], dp[v]);
    }
}
struct node
{
    int l, r, id;
    node(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) {}
};
vector<node> g[N];
ll answer[N];
inline void solve(int u)
{
    for (auto v : g[u])
        answer[v.id] = query(1, 1, n, v.l, v.r);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        tree[1].update(edge[i].dis);
        update(1, 1, n, v, dp[v], -2 * edge[i].dis);
        solve(v);
        tree[1].update(-edge[i].dis);
        update(1, 1, n, v, dp[v], 2 * edge[i].dis);
    }
}
signed main()
{
    read(n, m);
    for (int i = 2; i <= n; ++i)
    {
        int v, w;
        read(v, w);
        add_edge(v, i, w);
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, l, r;
        read(u, l, r);
        g[u].push_back(node(l, r, i));
    }
    dfs(1);
    build(1, 1, n);
    solve(1);
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}