#include <cstdio>
#include <random>
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
constexpr int N = 3e5 + 5;
int n, m;
int Log[N], f[N][25];
int a[N];
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
int dfn[N], low[N], dfstime;
int fa[N][25];
inline void dfs(int u, int _fa)
{
    dfn[u] = ++dfstime;
    fa[u][0] = _fa;
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
    low[u] = dfstime;
}
inline int jump(int u, int lim)
{
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] && fa[u][i] <= lim)
            u = fa[u][i];
    return fa[u][0];
}
struct tree_array
{
    ll c[N];
    inline void update(int u, int v)
    {
        // printf("%d %d %d %d\n", u, dfn[u], low[u], v);
        for (int i = dfn[u]; i <= dfstime; i += lowbit(i))
            c[i] += v;
        for (int i = low[u] + 1; i <= dfstime; i += lowbit(i))
            c[i] -= v;
    }
    inline ll query(int u)
    {
        ll res = 0;
        for (int i = dfn[u]; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
} ta;
struct Tree
{
    int ch[2];
    int key, val;
    int size;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
int root, cnt;
mt19937 rnd(233);
inline int newnode(int val, int rt = ++cnt)
{
    tree[rt].size = 1;
    tree[rt].key = (int)rnd();
    tree[rt].val = val;
    lc(rt) = rc(rt) = 0;
    return rt;
}
inline void pushup(int rt)
{
    tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size + 1;
}
inline void split(int rt, int size, int &x, int &y)
{
    if (!rt)
        x = y = 0;
    else
    {
        if (tree[lc(rt)].size < size)
        {
            x = rt;
            split(rc(rt), size - tree[lc(rt)].size - 1, rc(x), y);
            pushup(x);
        }
        else
        {
            y = rt;
            split(lc(rt), size, x, lc(y));
            pushup(y);
        }
    }
}
inline int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    else
    {
        if (tree[x].key > tree[y].key)
        {
            rc(x) = merge(rc(x), y);
            pushup(x);
            return x;
        }
        else
        {
            lc(y) = merge(x, lc(y));
            pushup(y);
            return y;
        }
    }
}
bool flag;
inline int find(int rt, int size)
{
    while (1)
    {
        // if (flag)
        // printf("%d %d %d\n", rt, tree[rt].size, size);
        if (tree[lc(rt)].size + 1 == size)
            return tree[rt].val;
        else if (tree[lc(rt)].size >= size)
            rt = lc(rt);
        else
        {
            size -= tree[lc(rt)].size + 1;
            rt = rc(rt);
        }
    }
}
inline int calc(int x, int y)
{
    return a[x] >= a[y] ? x : y;
}
inline int query(int l, int r)
{
    if (l > r)
        return 0;
    int k = Log[r - l + 1];
    return calc(f[l][k], f[r - (1 << k) + 1][k]);
}
inline int query(int x)
{
    return query(x, find(root, x));
}
inline void dfs(int u)
{
    if (!u)
        return;
    dfs(lc(u));
    printf(" %d", tree[u].val);
    dfs(rc(u));
}
int st[N], top;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
#endif
    Log[0] = -1;
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        f[i][0] = i;
        Log[i] = Log[i >> 1] + 1;
    }
    for (int j = 1; j <= Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            f[i][j] = calc(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    a[0] = 0x7fffffff;
    for (int i = n; i >= 1; --i)
    {
        while (top && a[st[top]] <= a[i])
            --top;
        add_edge(st[top], i);
        st[++top] = i;
    }
    dfs(0, 0);
    for (int i = 1; i <= n; ++i)
    {
        root = merge(root, newnode(i));
        ta.update(i, a[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        int opt, l, r;
        read(opt, l, r);
        int sta = query(l);
        if (opt == 1)
        {
            if (l == r)
                continue;
            int x, y, z;
            split(root, r, y, z);
            split(y, l - 1, x, y);
            int val = find(y, r - l + 1);
            int now;
            split(y, 1, now, y);
            y = merge(y, newnode(val, now));
            root = merge(x, merge(y, z));
            // printf("%d\n", sta);
            // dfs(root);
            // putchar('\n');
            if ((l == 1 || query(l - 1) != sta) && query(l) != sta)
                ta.update(sta, -a[sta]);
        }
        else
        {
            int ed = jump(sta, query(r));
            // flag = (i == 3);
            // printf("%d %d %d %d %d\n", sta, ed, r, query(r), find(root, r));
            // printf(" %d\n", ta.query(sta));
            printf("%lld\n", ta.query(sta) - ta.query(ed));
        }
    }
    return 0;
}
