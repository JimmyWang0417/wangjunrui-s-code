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
const int N = 6e5 + 5;
int n, m, q, h[N];
int p[N], tot;
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
int father[N];
inline int find(int x)
{
    return !father[x] ? x : father[x] = find(father[x]);
}
struct Tree
{
    int l, r;
    int size;
} tree[N * 100];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N], cnt;
inline void update(int pre, int &rt, int l, int r, int pos, int val)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    tree[rt].size += val;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos, val);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos, val);
}
inline int merge(int x, int y, int l, int r)
{
    if (!x || !y)
        return x | y;
    int rt = ++cnt;
    tree[rt].size = tree[x].size + tree[y].size;
    if (l == r)
        return rt;
    int mid = (l + r) >> 1;
    lc(rt) = merge(lc(x), lc(y), l, mid);
    rc(rt) = merge(rc(x), rc(y), mid + 1, r);
    return rt;
}
inline int query(int rt, int l, int r, int k_th)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (tree[rc(rt)].size >= k_th)
        return query(rc(rt), mid + 1, r, k_th);
    return query(lc(rt), l, mid, k_th - tree[rc(rt)].size);
}
struct node
{
    int u, v, w;
    inline bool operator<(const node &rhs) const
    {
        return w < rhs.w;
    }
} e[N];
int a[N];
int fa[N][25], g[N][25];
inline void dfs(int u, int _fa)
{
    //	printf("%d %d\n",u,a[u]);
    fa[u][0] = _fa;
    g[u][0] = a[_fa];
    for (int i = 0; i < 20; ++i)
    {
        fa[u][i + 1] = fa[fa[u][i]][i];
        g[u][i + 1] = max(g[u][i], g[fa[u][i]][i]);
    }
    if (!head[u])
    {
        update(root[u], root[u], 1, tot, h[u], 1);
        return;
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        root[u] = merge(root[u], root[v], 1, tot);
    }
}
inline void kruskal()
{
    sort(e + 1, e + 1 + m);
    a[0] = 0x7fffffff;
    for (int i = 1; i <= n; ++i)
        a[i] = ~0x7fffffff;
    int rt = n;
    for (int i = 1; i <= m; ++i)
    {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v)
            continue;
        ++rt;
        add_edge(rt, u), add_edge(rt, v);
        father[u] = father[v] = rt;
        a[rt] = e[i].w;
    }
    dfs(rt, 0);
}
inline int queryroot(int u, int x)
{
    for (int i = 20; i >= 0; --i)
        if (g[u][i] <= x)
            u = fa[u][i];
    return u;
}
inline void work()
{
    int u, x, k;
    read(u, x, k);
    int rt = root[queryroot(u, x)];
    //	printf("%d\n",g[u][20]);
    //	printf("%d\n",queryroot(u,x));
    if (tree[rt].size >= k)
        printf("%d\n", p[query(rt, 1, tot, k)]);
    else
        printf("-1\n");
}
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
    {
        read(h[i]);
        p[i] = h[i];
    }
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    p[0] = -1;
    for (int i = 1; i <= n; ++i)
        h[i] = (int)(lower_bound(p + 1, p + 1 + tot, h[i]) - p);
    for (int i = 1; i <= m; ++i)
        read(e[i].u, e[i].v, e[i].w);
    kruskal();
    while (q--)
        work();
    return 0;
}
