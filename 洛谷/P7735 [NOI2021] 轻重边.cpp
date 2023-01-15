/**
 *    unicode: UTF-8
 *    name:    P7735 [NOI2021] 轻重边
 *    author:  whitepaperdog
 *    created: 2022.07.27 周三 08:37:34 (Asia/Shanghai)
 **/
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
    int lcolor, rcolor, ans;
    node(int _lcolor = 0, int _rcolor = 0, int _ans = 0) : lcolor(_lcolor), rcolor(_rcolor), ans(_ans) {}
    inline node operator+(const node &rhs) const
    {
        if (!lcolor)
            return rhs;
        if (!rhs.rcolor)
            return (*this);
        return node(lcolor, rhs.rcolor, ans + rhs.ans + (rcolor == rhs.lcolor));
    }
};
struct Tree
{
    node ans;
    int size, tag;
    inline void update(int val)
    {
        tag = val;
        ans = node(val, val, size);
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].ans = tree[lc].ans + tree[rc].ans;
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
    tree[rt].size = r - l;
    tree[rt].tag = 0;
    if (l == r)
    {
        tree[rt].ans = node(l, l);
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
inline node query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return node();
    if (x <= l && r <= y)
        return tree[rt].ans;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
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
int fa[N], dep[N];
int dfn[N], dfstime;
int top[N];
inline void dfs1(int u, int _fa)
{
    size[u] = 1;
    dep[u] = dep[fa[u] = _fa] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
inline void dfs2(int u, int topf)
{
    dfn[u] = ++dfstime;
    top[u] = topf;
    if (son[u])
        dfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (dfn[v])
            continue;
        dfs2(v, v);
    }
}
inline void update(int x, int y, int val)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(1, 1, n, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y])
        swap(x, y);
    update(1, 1, n, dfn[x], dfn[y], val);
}
inline int query(int x, int y)
{
    node u = node(), v = node();
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
        {
            swap(x, y);
            swap(u, v);
        }
        u = query(1, 1, n, dfn[top[x]], dfn[x]) + u;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
    {
        swap(x, y);
        swap(u, v);
    }
    v = query(1, 1, n, dfn[x], dfn[y]) + v;
    return u.ans + v.ans + (u.lcolor == v.lcolor);
}
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        read(n, m);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            read(u, v);
            add_edge(u, v);
            add_edge(v, u);
        }
        dfs1(1, 0);
        dfs2(1, 1);
        build(1, 1, n);
        int cnt = n;
        for (int i = 1; i <= m; ++i)
        {
            int opt, x, y;
            read(opt, x, y);
            if (opt == 1)
                update(x, y, ++cnt);
            else
                printf("%d\n", query(x, y));
        }
        memset(head, num_edge = 0, sizeof(head));
        memset(dfn, dfstime = 0, sizeof(dfn));
        memset(son, 0, sizeof(son));
    }
    return 0;
}
