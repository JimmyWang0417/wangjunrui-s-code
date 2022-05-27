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
const int N = 3e5 + 5;
int n;
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
struct Tree
{
    int ch[2];
    int size;
} tree[N * 50];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
int cnt, root[N];
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
        update(lc(pre), rc(rt), mid + 1, r, pos, val);
}
inline int query(int rootl, int rootr, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rootr].size - tree[rootl].size;
    int mid = (l + r) >> 1;
    return query(lc(rootl), lc(rootr), l, mid, x, y) + query(rc(rootl), rc(rootr), mid + 1, r, x, y);
}
int size[N];
int dfn[N], dfstime, id[N];
int sum[N];
inline void dfs1(int u, int _fa)
{
    id[dfn[u] = ++dfstime] = u;
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        size[u] += size[v];
    }
}
int maxx[N], nxtmaxx[N];
inline void dfs2(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs2(v, u);
        if (maxx[u] < size[v])
        {
            nxtmaxx[u] = maxx[u];
            maxx[u] = size[v];
        }
        else
            nxtmaxx[u] = max(nxtmaxx[u], size[v]);
    }
    if (maxx[u] > n / 2)
    {
    }
}
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i)
    {
        update(root[i - 1], root[i], 1, n, size[id[i]], 1);
        ++sum[size[id[i]]];
    }
    dfs2(1, 0);
    return 0;
}
