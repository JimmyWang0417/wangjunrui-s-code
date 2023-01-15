/**
 *    unicode: UTF-8
 *    name:    P4719 【模板】"动态 DP"&动态树分治
 *    author:  whitepaperdog
 *    created: 2022.07.02 周六 16:30:23 (Asia/Shanghai)
 **/
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
int n, m, a[N];
struct node
{
    int a, b, c, d;
    node(int _a = 0, int _b = 0, int _c = 0, int _d = 0) : a(_a), b(_b), c(_c), d(_d) {}
    inline node operator*(const node &rhs) const
    {
        return node(max(a + rhs.a, b + rhs.c),
                    max(a + rhs.b, b + rhs.d),
                    max(c + rhs.a, d + rhs.c),
                    max(c + rhs.b, d + rhs.d));
    }
} data[N];
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
    node val;
    int fa, lc, rc;
} tree[N];
#define fa(x) tree[x].fa
#define lc(x) tree[x].lc
#define rc(x) tree[x].rc
inline void pushup(int rt)
{
    tree[rt].val = data[rt];
    if (lc(rt))
        tree[rt].val = tree[lc(rt)].val * tree[rt].val;
    if (rc(rt))
        tree[rt].val = tree[rt].val * tree[rc(rt)].val;
}
inline bool nroot(int x)
{
    return lc(fa(x)) == x || rc(fa(x)) == x;
}
int p[N], sum[N], tot;
inline void build(int &rt, int l, int r)
{
    if (l > r)
        return;
    int mid = (int)(lower_bound(sum + l, sum + r + 1, (sum[l - 1] + sum[r]) / 2) - sum);
    rt = p[mid];

    build(lc(rt), l, mid - 1);
    if (lc(rt))
        fa(lc(rt)) = rt;

    build(rc(rt), mid + 1, r);
    if (rc(rt))
        fa(rc(rt)) = rt;

    pushup(rt);
}
int size[N], son[N];
int dfn[N], dfstime;
int dp[N][2];
inline void dfs1(int u, int _fa)
{
    size[u] = 1;
    dp[u][1] = a[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        if (size[son[u]] < size[v])
            son[u] = v;
        size[u] += size[v];
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
    data[u] = node(dp[u][0] - max(dp[son[u]][0], dp[son[u]][1]),
                   dp[u][0] - max(dp[son[u]][0], dp[son[u]][1]),
                   dp[u][1] - dp[son[u]][0],
                   ~0x3f3f3f3f);
}
inline int dfs2(int u, int _fa)
{
    dfn[u] = ++dfstime;
    p[++tot] = u;
    int rt = 0;
    if (!son[u])
    {
        for (int i = 1; i <= tot; ++i)
            sum[i] = sum[i - 1] + size[p[i]] - size[son[p[i]]];
        build(rt, 1, tot);
        tot = 0;
        return rt;
    }
    else
        rt = dfs2(son[u], u);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || v == son[u])
            continue;
        fa(dfs2(v, u)) = u;
    }
    return rt;
}
inline void update(int rt)
{
    node las = tree[rt].val;
    pushup(rt);
    if (fa(rt) && !nroot(rt))
    {
        data[fa(rt)].a = (data[fa(rt)].b += max(tree[rt].val.a, tree[rt].val.c) - max(las.a, las.c));
        data[fa(rt)].c += tree[rt].val.a - las.a;
    }
    if (fa(rt))
        update(fa(rt));
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    int root = dfs2(1, 0);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        data[x].c += y - a[x];
        update(x);
        a[x] = y;
        printf("%d\n", max(tree[root].val.a, tree[root].val.c));
    }
    return 0;
}