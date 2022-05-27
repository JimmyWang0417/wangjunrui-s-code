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
const int N = 1e5 + 5;
inline void ckmin(int &x, int y)
{
    if (x > y)
        x = y;
}
struct Tree
{
    int l, r;
    int min;
} tree[N * 40];
int root[N], cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void update(int pre, int &rt, int l, int r, int pos, int val)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    tree[rt].min = min(tree[rt].min, val);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos, val);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos, val);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y || !rt)
        return 0x7fffffff;
    if (x <= l && r <= y)
        return tree[rt].min;
    int mid = (l + r) >> 1;
    return min(query(lc(rt), l, mid, x, y), query(rc(rt), mid + 1, r, x, y));
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
int dep[N];
int n, r, m, a[N];
int dfn[N], low[N], dfstime;
inline void dfs(int u, int _fa)
{
    dfn[u] = ++dfstime;
    dep[u] = dep[_fa] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
    low[u] = dfstime;
}
int p[N];
signed main()
{
    tree[0].min = 0x7fffffff;
    read(n, r);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(r, 0);
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    sort(p + 1, p + 1 + n, [](int x, int y)
         { return dep[x] < dep[y]; });
    for (int i = 1; i <= n; ++i)
        update(root[dep[p[i - 1]]], root[dep[p[i]]], 1, n, dfn[p[i]], a[p[i]]);
    int lastans = 0;
    read(m);
    while (m--)
    {
        int x, y;
        read(x, y);
        x = (x + lastans) % n + 1, y = (y + lastans) % n;
        printf("%d\n", lastans = query(root[min(dep[x] + y, dep[p[n]])], 1, n, dfn[x], low[x]));
    }
    return 0;
}
