/**
 *    unicode: UTF-8
 *    name:    P4211 [LNOI2014]LCA
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
constexpr int mod = 201314;
int n, m;
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
    unsigned size, ans, tag;
    inline void update(unsigned val)
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
    tree[rt].size = r - l + 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
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
inline unsigned query(int rt, int l, int r, int x, int y)
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
inline unsigned query(int x)
{
    unsigned res = 0;
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
    bool flag;
    inline bool operator<(const Query &rhs) const
    {
        return pos < rhs.pos;
    }
} q[N * 2];
int answer[N];
signed main()
{
    read(n, m);
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa);
        add_edge(_fa + 1, i);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    int cnt = 0;
    for (int i = 1; i <= m; ++i)
    {
        int l, r, x;
        read(l, r, x);
        if (l >= 1)
        {
            ++cnt;
            q[cnt].pos = l;
            q[cnt].u = x + 1;
            q[cnt].id = i;
            q[cnt].flag = false;
        }
        ++cnt;
        q[cnt].pos = r + 1;
        q[cnt].u = x + 1;
        q[cnt].id = i;
        q[cnt].flag = true;
    }
    sort(q + 1, q + 1 + cnt);
    for (int i = 1, j = 1; i <= n; ++i)
    {
        update(i);
        while (j <= cnt && q[j].pos == i)
        {
            if (q[j].flag)
                answer[q[j].id] += query(q[j].u);
            else
                answer[q[j].id] -= query(q[j].u);
            ++j;
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", (answer[i] + mod) % mod);
    return 0;
}