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
constexpr int N = 5e5 + 5;
constexpr int mod = 1e9 + 7;
int n, m, q;
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
int size[N], son[N];
int fa[N], dep[N];
inline void dfs1(int u, int _fa)
{
    size[u] = 1;
    dep[u] = dep[fa[u] = _fa] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
int dfn[N], dfstime;
int rk[N];
int top[N];
inline void dfs2(int u, int topf)
{
    top[u] = topf;
    rk[dfn[u] = ++dfstime] = u;
    if (son[u])
        dfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (top[v])
            continue;
        dfs2(v, v);
    }
}
int b[N];
struct Tree
{
    int cnt;
    int len;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].len = b[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    if (tree[rt].cnt)
        tree[rt].len = 0;
    else
        tree[rt].len = (tree[lc].len + tree[rc].len) % mod;
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        tree[rt].cnt += val;
        if (tree[rt].cnt)
            tree[rt].len = 0;
        else
        {
            if (l == r)
                tree[rt].len = b[l];
            else
                tree[rt].len = (tree[lc].len + tree[rc].len) % mod;
        }
        return;
    }
    int mid = (l + r) >> 1;
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    if (tree[rt].cnt)
        tree[rt].len = 0;
    else
        tree[rt].len = (tree[lc].len + tree[rc].len) % mod;
}
inline void update(int x, int y, int val)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(1, 1, n, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y])
        swap(x, y);
    if (dfn[x] < dfn[y])
        update(1, 1, n, dfn[x] + 1, dfn[y], val);
}
struct node
{
    int u, v, time, val;
    inline bool operator<(const node &rhs) const
    {
        return time < rhs.time;
    }
} a[N * 2];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("rhapsody.in", "r", stdin);
    freopen("rhapsody.out", "w", stdout);
#endif
    read(n, m, q);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
        b[i] = (int)(((ll)size[rk[i]] * (n - size[rk[i]])) % mod);
    build(1, 1, n);
    for (int i = 1; i <= q; ++i)
    {
        int l, r, u, v;
        read(l, r, u, v);
        a[i * 2 - 1] = (node){u, v, l, 1};
        a[i * 2] = (node){u, v, r + 1, -1};
    }
    sort(a + 1, a + 1 + 2 * q);
    int answer = 0;
    for (int i = 1, j = 1, now = 12345678; i <= m; ++i, now = (int)(now * 12345678ll % mod))
    {
        while (j <= 2 * q && a[j].time <= i)
        {
            update(a[j].u, a[j].v, a[j].val);
            ++j;
        }
        answer = (int)((answer + (ll)tree[1].len * now) % mod);
    }
    printf("%d\n", answer);
    return 0;
}
