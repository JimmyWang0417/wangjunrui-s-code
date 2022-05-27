#include <bits/stdc++.h>
#define int ll
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
const int N = 2e5 + 5;
const int mod = 998244353;
int n, m, a[N];
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge = 1;
int deg[N];
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
    ++deg[to];
}
struct Tree
{
    int add, mul;
    int sum, size;
    inline void addval(int val)
    {
        (add += val) %= mod;
        (sum += val * size) %= mod;
    }
    inline void times(int val)
    {
        (mul *= val) %= mod;
        (add *= val) %= mod;
        (sum *= val) %= mod;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
int p[N], tot;
inline void pushup(int rt)
{
    tree[rt].sum = (tree[lc].sum + tree[rc].sum) % mod;
}
inline void pushdown(int rt)
{
    if (tree[rt].mul != 1)
    {
        tree[lc].times(tree[rt].mul);
        tree[rc].times(tree[rt].mul);
        tree[rt].mul = 1;
    }
    if (tree[rt].add)
    {
        tree[lc].addval(tree[rt].add);
        tree[rc].addval(tree[rt].add);
        tree[rt].add = 0;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].sum = tree[rt].add = 0;
    tree[rt].mul = 1;
    tree[rt].size = p[r] - p[l - 1];
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void addval(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        tree[rt].addval(val);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    addval(lc, l, mid, x, y, val);
    addval(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline void times(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        tree[rt].times(val);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    times(lc, l, mid, x, y, val);
    times(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
bool flag;
int b[N], cnt;
int dfn[N], dfstime;
inline void dfs(int u, int lasedge)
{
    dfn[u] = ++dfstime;
    b[++cnt] = a[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (i == (lasedge ^ 1))
            continue;
        if (!dfn[v])
            dfs(v, i);
    }
}
inline int solve1()
{
    for (int i = 1; i <= cnt; ++i)
        p[i] = b[i];
    sort(p + 1, p + 1 + cnt);
    tot = (int)(unique(p + 1, p + 1 + cnt) - p - 1);
    for (int i = 1; i <= cnt; ++i)
        b[i] = (int)(lower_bound(p + 1, p + 1 + tot, b[i]) - p);
    build(1, 1, tot);
    addval(1, 1, tot, 1, b[1], 1);
    for (int i = 2; i <= cnt; ++i)
    {
        int res = tree[1].sum;
        tree[1].times(-1);
        tree[1].addval(res);
        times(1, 1, tot, b[i] + 1, tot, 0);
    }
    return tree[1].sum;
}
inline int solve2()
{
    int firstnumber = 1;
    for (int i = 1; i <= cnt; ++i)
    {
        p[i] = b[i];
        if (b[firstnumber] > b[i])
            firstnumber = i;
    }
    sort(p + 1, p + 1 + cnt);
    tot = (int)(unique(p + 1, p + 1 + cnt) - p - 1);
    for (int i = 1; i <= cnt; ++i)
        b[i] = (int)(lower_bound(p + 1, p + 1 + tot, b[i]) - p);
    build(1, 1, tot);
    addval(1, 1, tot, 1, b[firstnumber], 1);
    int res = 0;
    for (int i = firstnumber % cnt + 1; i != firstnumber; i = i % cnt + 1)
    {
        int x = tree[1].sum;
        tree[1].times(-1);
        tree[1].addval(x);
        times(1, 1, tot, b[i] + 1, tot, 0);
        res = (tree[1].sum - res) % mod;
    }
    return res;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    ll ans = 1;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i] && deg[i] <= 1)
        {
            cnt = 0;
            dfs(i, 0);
            (ans *= solve1()) %= mod;
        }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
        {
            cnt = 0;
            dfs(i, 0);
            (ans *= solve2()) %= mod;
        }
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}
