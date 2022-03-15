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
int size[N], son[N];
int dep[N], fa[N][25];
inline void dfs1(int u)
{
    size[u] = 1;
    dep[u] = dep[fa[u][0]] + 1;
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs1(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
int dfn[N], id[N], dfstime;
int top[N];
inline void dfs2(int u, int topf)
{
    top[u] = topf;
    id[dfn[u] = ++dfstime] = u;
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
struct Tree
{
    int size;
    int tag;
    ll sum;
    inline void update(int val)
    {
        tag += val;
        sum += (ll)val * size;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
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
    tree[rt].size = r - l + 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        tree[rt].update(val);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline void update(int x, int y, int val)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(1, 1, n, dfn[top[x]], dfn[x], val);
        x = fa[top[x]][0];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(1, 1, n, dfn[x], dfn[y], val);
}
inline int query(int rt, int l, int r, ll k_th)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (k_th <= tree[lc].sum)
        return query(lc, l, mid, k_th);
    else
        return query(rc, mid + 1, r, k_th - tree[lc].sum);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
inline int query()
{
    ll k_th = tree[1].sum / 2 + 1;
    int u = id[query(1, 1, n, k_th)];
    if (query(1, 1, n, dfn[u], dfn[u] + size[u] - 1) >= k_th)
        return u;
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] && query(1, 1, n, dfn[fa[u][i]], dfn[fa[u][i]] + size[fa[u][i]] - 1) < k_th)
            u = fa[u][i];
    return fa[u][0];
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("core.in","r",stdin);
    freopen("core.out","w",stdout);
#endif
    read(n, m);
    for (int i = 2; i <= n; ++i)
    {
        read(fa[i][0]);
        add_edge(fa[i][0], i);
    }
    dfs1(1);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, u, v;
        read(opt, u);
        if (opt == 1)
            update(1, 1, n, dfn[u], dfn[u] + size[u] - 1, 1);
        else
        {
            read(v);
            update(u, v, 1);
        }
        printf("%d\n", query());
    }
    return 0;
}