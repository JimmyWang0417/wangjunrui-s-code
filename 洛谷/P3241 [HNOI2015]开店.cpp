#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 1.5e5 + 5;
int n, q, A;
int a[N];
struct Edge
{
    int next, to, dis;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
struct Tree_array
{
    int n;
    vector<int> p;
    vector<ll> sum;
    inline void build()
    {
        sort(p.begin(), p.end());
        n = (int)p.size();
        sum.resize(n + 5);
    }
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            sum[i] += val;
    }
    inline ll query(int pos)
    {
        ll res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += sum[i];
        return res;
    }
    inline ll query(int l, int r)
    {
        return query((int)(upper_bound(p.begin(), p.end(), r) - p.begin())) -
               query((int)(lower_bound(p.begin(), p.end(), l) - p.begin()));
    }
    inline ll get(int l, int r)
    {
        return (int)(upper_bound(p.begin(), p.end(), r) - p.begin()) - (int)(lower_bound(p.begin(), p.end(), l) - p.begin());
    }
} tree[N];
int sum, size[N], maxsize[N], root;
bool vis[N];
inline void getroot(int u, int _fa)
{
    size[u] = 1;
    maxsize[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        getroot(v, u);
        size[u] += size[v];
        ckmax(maxsize[u], size[v]);
    }
    ckmax(maxsize[u], sum - size[u]);
    if (maxsize[root] > maxsize[u])
        root = u;
}
int fa[N][25], dis[N][25], cnt[N];
inline void dfs(int u, int _fa, int d)
{
    size[u] = 1;
    ++cnt[u];
    fa[u][cnt[u]] = root, dis[u][cnt[u]] = d;
    tree[root].p.push_back(a[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        dfs(v, u, d + edge[i].dis);
        size[u] += size[v];
    }
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    dfs(u, 0, 0);
    tree[u].build();
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = size[v];
        solve(v);
    }
}
inline void update(int u)
{
    for (int i = cnt[u]; i > 1; --i)
        tree[fa[u][i]].update((int)(lower_bound(tree[fa[u][i]].p.begin(), tree[fa[u][i]].p.end(), a[u]) - tree[fa[u][i]].p.begin() + 1), dis[u][i] - dis[u][i - 1]);
    tree[fa[u][1]].update((int)(lower_bound(tree[fa[u][1]].p.begin(), tree[fa[u][1]].p.end(), a[u]) - tree[fa[u][1]].p.begin() + 1), dis[u][1]);
}
inline ll query(int u, int l, int r)
{
    ll res = 0;
    for (int i = cnt[u]; i > 1; --i)
        res += tree[fa[u][i]].query(l, r);
    res += tree[fa[u][1]].query(l, r);
    for (int i = 1; i < cnt[u]; ++i)
        res += (ll)dis[u][i] * (tree[fa[u][i]].get(l, r) - tree[fa[u][i + 1]].get(l, r));
    return res;
}
signed main()
{
    read(n, q, A);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    maxsize[root = 0] = sum = n;
    solve(1);
    for (int i = 1; i <= n; ++i)
        update(i);
    ll lastans = 0;
    for (int i = 1; i <= q; ++i)
    {
        int u, l, r;
        read(u, l, r);
        l = (l + lastans) % A;
        r = (r + lastans) % A;
        if (l > r)
            swap(l, r);
        printf("%lld\n", lastans = query(u, l, r));
    }
    return 0;
}