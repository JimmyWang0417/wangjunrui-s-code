#include <algorithm>
#include <cstdio>
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
constexpr int N = 2e5 + 5;
int n, m, c, q;
struct Tree
{
    int l, r;
    int where;
} tree[N * 40];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline void update(int &rt, int l, int r, int pos, int val)
{
    ++cnt;
    tree[cnt] = tree[rt];
    rt = cnt;
    if (l == r)
    {
        tree[rt].where = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val);
    else
        update(rc(rt), mid + 1, r, pos, val);
}
inline int query(int rt, int l, int r, int pos)
{
    if (l == r)
        return tree[rt].where;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(lc(rt), l, mid, pos);
    else
        return query(rc(rt), mid + 1, r, pos);
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
int f[N][25], g[N][25];
int fa[N][25];
int p[N], a[N];
int where[N];
int dep[N];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    root[u] = root[_fa];
    update(root[u], 1, m, a[u], u);
    f[u][0] = (where[a[u]] == c ? 0 : query(root[u], 1, m, p[where[a[u]] + 1]));
    g[u][0] = (where[a[u]] == 1 ? 0 : query(root[u], 1, m, p[where[a[u]] - 1]));
    fa[u][0] = _fa;
    for (int i = 0; i < 18; ++i)
    {
        f[u][i + 1] = f[f[u][i]][i];
        g[u][i + 1] = g[g[u][i]][i];
        fa[u][i + 1] = fa[fa[u][i]][i];
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 18; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 18; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
inline bool check(int u, int lca, int res, int need)
{
    u = query(root[u], 1, m, p[res]);
    if (dep[u] >= dep[lca])
    {
        --res;
        for (int i = 18; i >= 0; --i)
            if (dep[g[u][i]] >= dep[lca])
            {
                u = g[u][i];
                res -= 1 << i;
            }
    }
    return res <= need;
}
inline void work()
{
    int u, v;
    read(u, v);
    int lca = getlca(u, v);
    int res = 0;
    u = query(root[u], 1, m, p[1]);
    if (dep[u] >= dep[lca])
    {
        ++res;
        for (int i = 18; i >= 0; --i)
            if (dep[f[u][i]] >= dep[lca])
            {
                res += 1 << i;
                u = f[u][i];
            }
    }
    int l = res + 1, r = c, ans = res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(v, lca, mid, res))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
}
signed main()
{
    read(n, m, c);
    for (int i = 1; i <= c; ++i)
    {
        read(p[i]);
        where[p[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    read(q);
    while (q--)
        work();
    return 0;
}
