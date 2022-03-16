#include <cstdio>
#include <vector>
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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
int n, a[N];
struct Tree
{
    int l, r;
    int sum;
    int mul;
    inline void update(int val)
    {
        sum = (int)((ll)sum * val % mod);
        mul = (int)((ll)mul * val % mod);
    }
} tree[N * 60];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline int newnode()
{
    ++cnt;
    tree[cnt].mul = 1;
    return cnt;
}
inline void pushup(int rt) { tree[rt].sum = (tree[lc(rt)].sum + tree[rc(rt)].sum) % mod; }
inline void pushdown(int rt)
{
    if (tree[rt].mul != 1)
    {
        if (lc(rt))
            tree[lc(rt)].update(tree[rt].mul);
        if (rc(rt))
            tree[rc(rt)].update(tree[rt].mul);
        tree[rt].mul = 1;
    }
}
inline void update(int &rt, int l, int r, int pos, int val)
{
    if (!rt)
        rt = newnode();
    if (l == r)
    {
        (tree[rt].sum += val) %= mod;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val);
    else
        update(rc(rt), mid + 1, r, pos, val);
    pushup(rt);
}
inline int merge(int x, int y, int l, int r)
{
    if (!x || !y)
        return x | y;
    if (l == r)
    {
        (tree[x].sum += tree[y].sum) %= mod;
        return x;
    }
    int mid = (l + r) >> 1;
    pushdown(x), pushdown(y);
    lc(x) = merge(lc(x), lc(y), l, mid);
    rc(x) = merge(rc(x), rc(y), mid + 1, r);
    pushup(x);
    return x;
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (!rt || r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return (query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y)) % mod;
}
vector<int> g[N];
int size[N], son[N];
int fa[N], dis[N];
inline void init(int u, int _fa)
{
    dis[u] = dis[fa[u] = _fa] + a[u];
    if (_fa)
        for (auto it = g[u].begin(); it != g[u].end(); ++it)
            if (*it == _fa)
            {
                g[u].erase(it);
                break;
            }
    size[u] = 1;
    for (auto v : g[u])
    {
        init(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
    if (son[u])
    {
        for (auto it = g[u].begin(); it != g[u].end(); ++it)
            if (*it == son[u])
            {
                g[u].erase(it);
                break;
            }
        g[u].insert(g[u].begin(), son[u]);
    }
}
inline void print(int rt, int l, int r)
{
    if (!rt)
        return;
    if (l == r)
    {
        printf("%d %d\n", l, tree[rt].sum);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    print(lc(rt), l, mid);
    print(rc(rt), mid + 1, r);
}
ll pre[N], suf[N];
ll dp[N];
inline ll calc(int rt, int l, int r, int all, int queryrt)
{
    if (!rt)
        return 0;
    if (l == r)
        return (ll)tree[rt].sum * query(queryrt, -1e9, 1e9, all - l, 1e9) % mod;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return (calc(lc(rt), l, mid, all, queryrt) + calc(rc(rt), mid + 1, r, all, queryrt)) % mod;
}
inline void dfs(int u)
{
    if (!son[u])
    {
        if (a[u] >= 0)
            dp[u] = 1;
        update(root[u], -1e9, 1e9, dis[u], 1);
        return;
    }
    for (auto v : g[u])
        dfs(v);
    pre[0] = suf[g[u].size()] = 1;
    for (int i = 0; i < (int)g[u].size(); ++i)
    {
        int v = g[u][i];
        pre[i] = i > 0 ? pre[i - 1] * dp[v] % mod : dp[v];
    }
    for (int i = (int)g[u].size() - 1; i >= 0; --i)
    {
        int v = g[u][i];
        suf[i] = suf[i + 1] * dp[v] % mod;
    }
    root[u] = root[son[u]];
    dp[u] = ((a[u] >= 0 ? suf[0] : 0) + query(root[u], -1e9, 1e9, dis[fa[u]], 1e9) * suf[1]) % mod;
    update(root[u], -1e9, 1e9, dis[u], dp[son[u]]);
    for (int i = 1; i < (int)g[u].size(); ++i)
    {
        int v = g[u][i];
        (dp[u] += calc(root[v], -1e9, 1e9, dis[u] + dis[fa[u]], root[u]) * suf[i + 1] % mod) %= mod;
        tree[root[u]].update(dp[v]);
        tree[root[v]].update(pre[i - 1]);
        root[u] = merge(root[u], root[v], -1e9, 1e9);
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("run.in", "r", stdin);
    freopen("run.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    tree[0].mul = 1;
    init(1, 0);
    dfs(1);
    printf("%lld\n", dp[1]);
    return 0;
}
