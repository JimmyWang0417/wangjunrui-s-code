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
constexpr int N = 1e5 + 5;
int n, m, q;
class SMALLTREE
{
public:
    struct Tree
    {
        int l, r, size;
    } tree[N * 40];
    int root[N], cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
    inline void update(int pre, int &rt, int l, int r, int pos)
    {
        rt = ++cnt;
        tree[rt] = tree[pre];
        ++tree[rt].size;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc(pre), lc(rt), l, mid, pos);
        else
            update(rc(pre), rc(rt), mid + 1, r, pos);
    }
    inline int query(int pre, int rt, int l, int r, int k_th)
    {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        int all = tree[lc(rt)].size - tree[lc(pre)].size;
        if (k_th <= all)
            return query(lc(pre), lc(rt), l, mid, k_th);
        else
            return query(rc(pre), rc(rt), mid + 1, r, k_th - all);
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
    int dfn[N], low[N], dfstime;
    int rk[N];
    int fa[N][20];
    inline void dfs(int u, int _fa)
    {
        rk[dfn[u] = ++dfstime] = u;
        dep[u] = dep[fa[u][0] = _fa] + 1;
        for (int i = 0; i < 18; ++i)
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
    inline int getdis(int u, int v)
    {
        if (dep[u] < dep[v])
            swap(u, v);
        int res = 0;
        for (int i = 18; i >= 0; --i)
            if (dep[fa[u][i]] >= dep[v])
            {
                res += (1 << i);
                u = fa[u][i];
            }
        if (u == v)
            return res;
        for (int i = 18; i >= 0; --i)
            if (fa[u][i] != fa[v][i])
            {
                res += (1 << (i + 1));
                u = fa[u][i];
                v = fa[v][i];
            }
        return res + 2;
    }
    inline void init()
    {
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            read(u, v);
            add_edge(u, v);
            add_edge(v, u);
        }
        dfs(1, 0);
        for (int i = 1; i <= n; ++i)
            update(root[i - 1], root[i], 1, n, rk[i]);
    }
} small;
class BIGTREE
{
public:
    int tot;
    ll sum[N];
    int fa[N][20];
    int pre[N];
    ll link[N];
    int dep[N];
    ll dist[N][20];
    inline int getroot(ll u)
    {
        int l = 1, r = tot, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (u <= sum[mid])
            {
                ans = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        return ans;
    }
    inline int calc(ll u)
    {
        int rt = getroot(u);
        return small.query(small.root[small.dfn[pre[rt]] - 1], small.root[small.low[pre[rt]]], 1, n, (int)(u - sum[rt - 1]));
    }
    inline void init()
    {
        tot = 1;
        pre[tot] = 1;
        dep[tot] = 1;
        sum[tot] = n;
        for (int i = 1; i <= m; ++i)
        {
            int x;
            ll to;
            read(to, x);
            int rt = getroot(to);
            ++tot;
            pre[tot] = x;
            link[tot] = to;
            fa[tot][0] = rt;
            dep[tot] = dep[rt] + 1;
            dist[tot][0] = small.dep[calc(to)] - small.dep[pre[rt]] + 1;
            sum[tot] = sum[tot - 1] + small.low[x] - small.dfn[x] + 1;
            for (int j = 0; j < 18; ++j)
            {
                fa[tot][j + 1] = fa[fa[tot][j]][j];
                dist[tot][j + 1] = dist[tot][j] + dist[fa[tot][j]][j];
            }
        }
    }
    inline ll solve(ll u, ll v)
    {
        int rtu = getroot(u), rtv = getroot(v);
        if (rtu == rtv)
            return small.getdis(calc(u), calc(v));
        if (dep[rtu] < dep[rtv])
        {
            swap(rtu, rtv);
            swap(u, v);
        }
        ll res = small.dep[calc(u)] - small.dep[pre[rtu]];
        u = rtu;
        for (int i = 18; i >= 0; --i)
            if (dep[fa[u][i]] > dep[rtv])
            {
                res += dist[u][i];
                u = fa[u][i];
            }
        if (getroot(link[u]) == rtv)
            return res + 1 + small.getdis(calc(link[u]), calc(v));
        res += small.dep[calc(v)] - small.dep[pre[rtv]];
        v = rtv;
        if (dep[u] > dep[v])
        {
            res += dist[u][0];
            u = fa[u][0];
        }
        for (int i = 18; i >= 0; --i)
            if (fa[u][i] != fa[v][i])
            {
                res += dist[u][i] + dist[v][i];
                u = fa[u][i];
                v = fa[v][i];
            }
        u = link[u], v = link[v];
        return res + 2 + small.getdis(calc(u), calc(v));
    }
} big;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("deployment.in", "r", stdin);
    freopen("deployment.out", "w", stdout);
#endif
    read(n, m, q);
    small.init();
    big.init();
    for (int i = 1; i <= q; ++i)
    {
        ll u, v;
        read(u, v);
        printf("%lld\n", big.solve(u, v));
    }
    return 0;
}
