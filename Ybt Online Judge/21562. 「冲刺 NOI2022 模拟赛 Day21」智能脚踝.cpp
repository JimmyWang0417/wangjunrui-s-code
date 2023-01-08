#include <algorithm>
#include <cstdio>
#include <vector>
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
int n, m, type;
struct node
{
    int u, v, w;
} a[N];
int b[N * 2];
int fa[N * 2];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
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
vector<int> g[N * 2];
int dfn[N], low[N], dfstime;
int L[N * 2], R[N * 2];
int f[N * 2][25];
inline void dfs(int u, int _fa)
{
    dfn[u] = ++dfstime;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
    low[u] = dfstime;
}
inline void solve(int u, int _fa)
{
    f[u][0] = _fa;
    for (int i = 0; i < 20; ++i)
        f[u][i + 1] = f[f[u][i]][i];
    if (g[u].empty())
    {
        L[u] = R[u] = ++dfstime;
        return;
    }
    L[u] = dfstime + 1;
    for (auto v : g[u])
        solve(v, u);
    R[u] = dfstime;
}
inline int calc(int u, int d)
{
    for (int i = 20; i >= 0; --i)
        if (b[f[u][i]] >= d)
            u = f[u][i];
    return u;
}
struct Tree
{
    int l, r;
    ll sum;
} tree[N * 400];
int root[N], cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void update(int &rt, int l, int r, int pos, int val)
{
    if (!rt)
        rt = ++cnt;
    tree[rt].sum += val;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val);
    else
        update(rc(rt), mid + 1, r, pos, val);
}
inline ll query(int rt, int l, int r, int pos)
{
    if (!rt)
        return 0;
    if (l == r)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(lc(rt), l, mid, pos);
    else
        return tree[lc(rt)].sum + query(rc(rt), mid + 1, r, pos);
}
inline void update(int posx, int posy, int val)
{
    if (posx <= n && posy <= n)
        for (int i = posx; i <= n; i += lowbit(i))
            update(root[i], 1, n, posy, val);
}
inline ll query(int posx, int posy)
{
    ll res = 0;
    for (int i = posx; i >= 1; i -= lowbit(i))
        res += query(root[i], 1, n, posy);
    return res;
}
inline void add(int x1, int y1, int x2, int y2, int val)
{
    update(x1, y1, val);
    update(x2 + 1, y1, -val);
    update(x1, y2 + 1, -val);
    update(x2 + 1, y2 + 1, val);
}
int c[N];
signed main()
{
    printf("%lu\n", sizeof(tree) / (1 << 20));
#ifdef ONLINE_JUDGE
    freopen("ankle.in", "r", stdin);
    freopen("ankle.ans", "w", stdout);
#endif
    read(n, m, type);
    for (int i = 1; i <= n; ++i)
        read(c[i]);
    for (int i = 1; i < n; ++i)
    {
        read(a[i].u, a[i].v, a[i].w);
        add_edge(a[i].u, a[i].v);
        add_edge(a[i].v, a[i].u);
    }
    sort(a + 1, a + n, [](const node &x, const node &y)
         { return x.w > y.w; });
    dfs(1, 0);
    b[0] = ~0x7fffffff;
    for (int i = 1; i < n; ++i)
    {
        g[i + n].push_back(find(a[i].u));
        g[i + n].push_back(find(a[i].v));
        b[i + n] = a[i].w;
        fa[find(a[i].u)] = fa[find(a[i].v)] = i + n;
    }
    dfstime = 0;
    solve(2 * n - 1, 0);
    ll lastans = 0;
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y, z;
        read(opt, x);
        if (opt == 1)
        {
            if (type)
                x = (int)((x + lastans) % n + 1);
            printf("%lld\n", lastans = query(dfn[x], L[x]) + c[x]);
        }
        else
        {
            read(y, z);
            if (type)
                z = (int)((z + lastans) % n + 1);
            int u = calc(z, y);
            add(dfn[z], L[u], low[z], R[u], x);
        }
    }
    return 0;
}
