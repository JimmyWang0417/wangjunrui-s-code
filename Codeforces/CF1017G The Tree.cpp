#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 1e5 + 5;
int n, m;
struct node
{
    int suf, sum;
    node(int _suf = INT_MIN / 2, int _sum = 0) : suf(_suf), sum(_sum) {}
    inline node operator+(const node &rhs) const
    {
        return node(max(suf + rhs.sum, rhs.suf), sum + rhs.sum);
    }
};
struct Tree
{
    node ans;
    int size;
    bool flag;
    inline void update()
    {
        flag = true;
        ans.sum = -size;
        ans.suf = -1;
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
    if (tree[rt].flag)
    {
        tree[lc].update();
        tree[rc].update();
        tree[rt].flag = false;
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
inline void cover(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update();
    int mid = (l + r) >> 1;
    pushdown(rt);
    cover(lc, l, mid, x, y);
    cover(rc, mid + 1, r, x, y);
    pushup(rt);
}
inline void add(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].ans.sum += tree[rt].size * val;
        tree[rt].ans.suf += val;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        add(lc, l, mid, pos, val);
    else
        add(rc, mid + 1, r, pos, val);
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
int dfn[N], dfstime;
int size[N], son[N];
int top[N], fa[N];
inline void dfs1(int u, int _fa)
{
    fa[u] = _fa;
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
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
inline int query(int x)
{
    node res;
    while (top[x] != 1)
    {
        res = query(1, 1, n, dfn[top[x]], dfn[x]) + res;
        x = fa[top[x]];
    }
    return (query(1, 1, n, dfn[1], dfn[x]) + res).suf;
}
signed main()
{
    read(n, m);
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa);
        add_edge(_fa, i);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    cover(1, 1, n, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, x;
        read(opt, x);
        if (opt == 1)
            add(1, 1, n, dfn[x], 1);
        else if (opt == 2)
        {
            cover(1, 1, n, dfn[x], dfn[x] + size[x] - 1);
            add(1, 1, n, dfn[x], -query(x) - 1);
        }
        else
            puts(query(x) >= 0 ? "black" : "white");
    }
    return 0;
}