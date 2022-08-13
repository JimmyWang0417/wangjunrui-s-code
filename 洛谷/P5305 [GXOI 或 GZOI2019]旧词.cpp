/**
 *    unicode: UTF-8
 *    name:    P5305 [GXOI/GZOI2019]旧词
 *    author:  wangjunrui
 *    created: 2022.07.30 周六 12:25:31 (Asia/Shanghai)
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
constexpr int N = 5e4 + 5;
constexpr int mod = 998244353;
inline ll quickpow(ll a, int b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
int n, m, k;
ll power[N];
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
int fa[N], dep[N];
int dfn[N], rk[N], dfstime;
int size[N], son[N];
int top[N];
inline void dfs1(int u, int _fa)
{
    dep[u] = dep[fa[u] = _fa] + 1;
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs1(v, u);
        if (size[son[u]] < size[v])
            son[u] = v;
        size[u] += size[v];
    }
}
inline void dfs2(int u, int topf)
{
    rk[dfn[u] = ++dfstime] = u;
    top[u] = topf;
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
struct Tree
{
    ll size, ans;
    int tag;
    inline void update(int val)
    {
        (ans += size * val) %= mod;
        (tag += val) %= mod;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].ans = (tree[lc].ans + tree[rc].ans) % mod;
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
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].size = power[dep[rk[l]]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[rt].size = (tree[lc].size + tree[rc].size) % mod;
}
inline void update(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        tree[rt].update(1);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y);
    update(rc, mid + 1, r, x, y);
    pushup(rt);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].ans;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return (query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y)) % mod;
}
inline void update(int x)
{
    while (top[x] != 1)
    {
        update(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    update(1, 1, n, 1, dfn[x]);
}
inline ll query(int x)
{
    ll res = 0;
    while (top[x] != 1)
    {
        (res += query(1, 1, n, dfn[top[x]], dfn[x])) %= mod;
        x = fa[top[x]];
    }
    (res += query(1, 1, n, 1, dfn[x])) %= mod;
    return res;
}
struct Query
{
    int pos, u, id;
    inline bool operator<(const Query &rhs) const
    {
        return pos < rhs.pos;
    }
} q[N * 2];
ll answer[N];
signed main()
{
    read(n, m, k);
    for (int i = 1; i <= n; ++i)
        power[i] = quickpow(i, k);
    for (int i = n; i >= 2; --i)
        (power[i] -= power[i - 1]) %= mod;
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa);
        add_edge(_fa, i);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].pos, q[i].u);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    for (int i = 1, j = 1; i <= n; ++i)
    {
        update(i);
        while (j <= m && q[j].pos == i)
        {
            answer[q[j].id] = query(q[j].u);
            ++j;
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", (answer[i] + mod) % mod);
    return 0;
}