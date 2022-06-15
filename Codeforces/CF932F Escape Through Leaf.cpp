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
int n, a[N], b[N];
struct node
{
    int k;
    ll b;
    node(int _k = 0, ll _b = 1e18) : k(_k), b(_b) {}
    inline ll calc(int x)
    {
        return (ll)k * x + b;
    }
};
struct Tree
{
    node val;
    int l, r;
} tree[N * 50];
int root[N], cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void update(int &rt, int l, int r, node val)
{
    if (!rt)
    {
        tree[rt = ++cnt].val = val;
        return;
    }
    int mid = (l + r) >> 1;
    ll now = val.calc(mid), res = tree[rt].val.calc(mid);
    if (l == r)
    {
        if (now > res)
            tree[rt].val = val;
        return;
    }
    if (val.k > tree[rt].val.k)
    {
        if (now < res)
        {
            update(rc(rt), mid + 1, r, tree[rt].val);
            tree[rt].val = val;
        }
        else
            update(lc(rt), l, mid, val);
    }
    else if (val.k < tree[rt].val.k)
    {
        if (now < res)
        {
            update(lc(rt), l, mid, tree[rt].val);
            tree[rt].val = val;
        }
        else
            update(rc(rt), mid + 1, r, val);
    }
    else if (now < res)
        tree[rt].val = val;
}
inline ll query(int rt, int l, int r, int pos)
{
    if (!rt)
        return 1e18;
    if (l == r)
        return tree[rt].val.calc(pos);
    int mid = (l + r) >> 1;
    return min(tree[rt].val.calc(pos), pos <= mid ? query(lc(rt), l, mid, pos) : query(rc(rt), mid + 1, r, pos));
}
inline void merge(int &x, int y, int l, int r)
{
    if (!x || !y)
    {
        x = x | y;
        return;
    }
    int mid = (l + r) >> 1;
    ll res = tree[x].val.calc(mid), now = tree[y].val.calc(mid);
    if (res > now)
        swap(x, y);
    if (l == r)
        return;
    merge(lc(x), lc(y), l, mid);
    merge(rc(x), rc(y), mid + 1, r);
    if (tree[x].val.k < tree[y].val.k)
        update(lc(x), l, mid, tree[y].val);
    else if (tree[x].val.k > tree[y].val.k)
        update(rc(x), mid + 1, r, tree[y].val);
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
ll dp[N];
inline void dfs(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        merge(root[u], root[v], -1e5, 1e5);
    }
    if (!root[u])
        update(root[u], -1e5, 1e5, node(b[u], 0));
    else
        update(root[u], -1e5, 1e5, node(b[u], dp[u] = query(root[u], -1e5, 1e5, a[u])));
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%lld ", dp[i]);
    putchar('\n');
    return 0;
}