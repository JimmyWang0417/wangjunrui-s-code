/**
 *    unicode: UTF-8
 *    name:    P4069 [SDOI2016]游戏
 *    author:  whitepaperdog
 *    created: 2022.08.09 周二 12:00:17 (Asia/Shanghai)
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
constexpr int N = 1e5 + 5;
int n, m;
struct node
{
    node(int _k = 0, ll _b = 0) : k(_k), b(_b) {}
    int k;
    ll b;
    inline ll calc(ll x) { return k * x + b; }
};
struct Edge
{
    int next, to, dis;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int size[N], son[N];
int fa[N], dep[N];
int dfn[N], rk[N], dfstime;
int top[N];
ll dis[N];
inline void dfs1(int u, int _fa)
{
    dep[u] = dep[fa[u] = _fa] + 1;
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dis[v] = dis[u] + edge[i].dis;
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
inline void dfs2(int u, int topf)
{
    rk[dfn[u] = ++dfstime] = u;
    top[u] = topf;
    if (son[u])
        dfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (top[v])
            continue;
        dfs2(v, v);
    }
}
struct Tree
{
    ll min;
    node val;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    tree[rt].val = node(0, tree[rt].min = 123456789123456789);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int x, int y, node val)
{
    if (r < x || l > y)
        return;
    if (l == r)
    {
        ckmin(tree[rt].min, val.calc(dis[rk[l]]));
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= l && r <= y)
    {
        ckmin(tree[rt].min, min(val.calc(dis[rk[l]]), val.calc(dis[rk[r]])));
        ll now = val.calc(dis[rk[mid]]), res = tree[rt].val.calc(dis[rk[mid]]);
        if (val.k < tree[rt].val.k)
        {
            if (now < res)
            {
                update(lc, l, mid, x, y, tree[rt].val);
                tree[rt].val = val;
            }
            else
                update(rc, mid + 1, r, x, y, val);
        }
        else if (val.k > tree[rt].val.k)
        {
            if (now < res)
            {
                update(rc, mid + 1, r, x, y, tree[rt].val);
                tree[rt].val = val;
            }
            else
                update(lc, l, mid, x, y, val);
        }
        else
            ckmin(tree[rt].val.b, val.b);
        return;
    }
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    ckmin(tree[rt].min, min(tree[lc].min, tree[rc].min));
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 123456789123456789;
    if (x <= l && r <= y)
        return tree[rt].min;
    int mid = (l + r) >> 1;
    return min(min(tree[rt].val.calc(dis[rk[max(l, x)]]), tree[rt].val.calc(dis[rk[min(r, y)]])),
               min(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y)));
}
inline int __lca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}
inline void update(int begx, int begy, int a, int b)
{
    int x = begx, y = begy;
    int lca = __lca(x, y);
    while (top[x] != top[lca])
    {
        update(1, 1, n, dfn[top[x]], dfn[x], node(-a, a * dis[begx] + b));
        x = fa[top[x]];
    }
    update(1, 1, n, dfn[lca], dfn[x], node(-a, a * dis[begx] + b));
    while (top[y] != top[lca])
    {
        update(1, 1, n, dfn[top[y]], dfn[y], node(a, a * (dis[begx] - 2 * dis[lca]) + b));
        y = fa[top[y]];
    }
    update(1, 1, n, dfn[lca], dfn[y], node(a, a * (dis[begx] - 2 * dis[lca]) + b));
}
inline ll query(int x, int y)
{
    ll res = 123456789123456789;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ckmin(res, query(1, 1, n, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ckmin(res, query(1, 1, n, dfn[x], dfn[y]));
    return res;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y, a, b;
        read(opt, x, y);
        if (opt == 1)
        {
            read(a, b);
            update(x, y, a, b);
        }
        else
            printf("%lld\n", query(x, y));
    }
    return 0;
}