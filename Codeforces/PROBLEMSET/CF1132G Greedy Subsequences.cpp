#include <algorithm>
#include <climits>
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
constexpr int N = 1e6 + 5;
int n, m;
int a[N];
int st[N], top;
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
int fa[N][25], dep[N], Log[N];
int dfn[N], low[N], dfstime;
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    fa[u][0] = _fa;
    for (int i = 0; i < Log[dep[u]]; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
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
inline int getfa(int u, int r)
{
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (fa[u][i] && fa[u][i] <= r)
            u = fa[u][i];
    return fa[u][0];
}
inline int calc(int u, int r)
{
    return dep[u] - dep[getfa(u, r)];
}
struct Tree
{
    int max;
    int tag;
    inline void update(int val)
    {
        max += val;
        tag += val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].max = max(tree[lc].max, tree[rc].max);
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
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].max = val;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
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
int answer[N];
signed main()
{
    read(n, m);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        Log[i] = Log[i >> 1] + 1;
    }
    st[0] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        while (top && a[st[top]] <= a[i])
            --top;
        add_edge(st[top], i);
        st[++top] = i;
    }
    dfs(n + 1, 0);
    for (int i = n - m + 1; i <= n; ++i)
        update(1, 1, dfstime, dfn[i], calc(i, n));
    answer[n - m + 1] = tree[1].max;
    for (int i = n - m; i >= 1; --i)
    {
        update(1, 1, dfstime, dfn[i + m], low[i + m], -1);
        update(1, 1, dfstime, dfn[i], calc(i, i + m - 1));
        answer[i] = tree[1].max;
    }
    for (int i = 1; i <= n - m + 1; ++i)
        printf("%d ", answer[i]);
    putchar('\n');
    return 0;
}