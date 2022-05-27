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
int n, q;
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
struct Tree
{
    int l, r;
    int size;
    ll sum;
} tree[N * 400];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N], cnt;
inline void update(int pre, int &rt, ll l, ll r, ll pos)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    ++tree[rt].size;
    tree[rt].sum += pos;
    if (l == r)
        return;
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos);
}
inline int querysize(int rootl, int rootr, ll l, ll r, ll pos)
{
    if (!rootr)
        return 0;
    if (l == r)
        return tree[rootr].size - tree[rootl].size;
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        return querysize(lc(rootl), lc(rootr), l, mid, pos) + tree[rc(rootr)].size - tree[rc(rootl)].size;
    else
        return querysize(rc(rootl), rc(rootr), mid + 1, r, pos);
}
inline ll querysum(int rootl, int rootr, ll l, ll r, ll pos)
{
    if (!rootr)
        return 0;
    if (l == r)
        return tree[rootr].sum - tree[rootl].sum;
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        return querysum(lc(rootl), lc(rootr), l, mid, pos) + tree[rc(rootr)].sum - tree[rc(rootl)].sum;
    else
        return querysum(rc(rootl), rc(rootr), mid + 1, r, pos);
}
int rk[N], dfn[N], dfstime, low[N];
ll dep[N];
inline void dfs(int u)
{
    rk[dfn[u] = ++dfstime] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dep[v] = dep[u] + edge[i].dis;
        dfs(v);
    }
    low[u] = dfstime;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("distance.in", "r", stdin);
    freopen("distance.out", "w", stdout);
#endif
    read(n);
    for (int i = 2; i <= n; ++i)
    {
        int _fa, w;
        read(_fa, w);
        add_edge(_fa, i, w);
    }
    dfs(1);
    for (int i = 1; i <= n; ++i)
        update(root[i - 1], root[i], 0, 2e14, dep[rk[i]]);
    read(q);
    while (q--)
    {
        int x, k;
        read(x, k);
        printf("%lld\n", querysum(root[dfn[x] - 1], root[low[x]], 0, 2e14, dep[x] + k) - (ll)querysize(root[dfn[x] - 1], root[low[x]], 0, 2e14, dep[x] + k) * dep[x]);
    }
    return 0;
}
