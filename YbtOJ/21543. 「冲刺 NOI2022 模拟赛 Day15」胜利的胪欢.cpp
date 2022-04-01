#include <cmath>
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
constexpr int N = 2e5 + 5, M = 8e6 + 5;
int n;
ll maxx;
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
struct Tree
{
    int l, r;
    ll sum;
} tree[M];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline void update(int &rt, ll l, ll r, ll pos, int val)
{
    if (!rt)
        rt = ++cnt;
    tree[rt].sum += val;
    if (l == r)
        return;
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val);
    else
        update(rc(rt), mid + 1, r, pos, val);
}
inline void merge(int &x, int y, ll l, ll r)
{
    if (!x || !y)
    {
        x |= y;
        return;
    }
    tree[x].sum += tree[y].sum;
    if (l == r)
        return;
    ll mid = (l + r) >> 1;
    merge(lc(x), lc(y), l, mid);
    merge(rc(x), rc(y), mid + 1, r);
}
inline ll updatel(int rt, ll l, ll r, ll val)
{
    tree[rt].sum -= val;
    if (l == r)
        return l;
    ll mid = (l + r) >> 1;
    if (val <= tree[lc(rt)].sum)
        return updatel(lc(rt), l, mid, val);
    else
    {
        val -= tree[lc(rt)].sum;
        lc(rt) = 0;
        return updatel(rc(rt), mid + 1, r, val);
    }
}
inline ll updater(int rt, ll l, ll r, ll val)
{
    tree[rt].sum -= val;
    if (l == r)
        return l;
    ll mid = (l + r) >> 1;
    if (val <= tree[rc(rt)].sum)
        return updater(rc(rt), mid + 1, r, val);
    else
    {
        val -= tree[rc(rt)].sum;
        rc(rt) = 0;
        return updater(lc(rt), l, mid, val);
    }
}
int c[N], d[N];
struct node
{
    ll l, r, max, where;
} a[N];
ll dis[N];
inline void dfs(int u)
{
    if (!head[u])
    {
        a[u].l = a[u].r = dis[u];
        a[u].max = d[u];
        update(root[u], 0, maxx, dis[u], d[u] * 2);
        return;
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dis[v] = dis[u] + c[v];
        dfs(v);
        a[u].max += a[v].max;
        merge(root[u], root[v], 0, maxx);
    }
    a[u].l = a[u].r = -1;
    if (u != 1 && d[u] < a[u].max)
    {
        a[u].l = updatel(root[u], 0, maxx, a[u].max - d[u]);
        a[u].r = updater(root[u], 0, maxx, a[u].max - d[u]);
        a[u].max = d[u];
    }
}
inline void solve(int u, ll val)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        a[v].where = c[v];
        ll res = val;
        if (a[v].l != -1)
        {
            if (res < a[v].l)
            {
                a[v].where -= a[v].l - res;
                res = a[v].l;
            }
            else if (res > a[v].r)
            {
                a[v].where += res - a[v].r;
                res = a[v].r;
            }
        }
        solve(v, res);
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
#endif
    read(n);
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        read(fa, c[i], d[i]);
        add_edge(fa, i);
        maxx += c[i];
    }
    dfs(1);
    solve(1, updatel(root[1], 0, maxx, a[1].max));
    ll ans = 0;
    for (int i = 2; i <= n; ++i)
        ans += abs(a[i].where - c[i]) * d[i];
    printf("%lld\n", ans);
    for (int i = 2; i <= n; ++i)
        printf("%lld\n", a[i].where);
    return 0;
}
