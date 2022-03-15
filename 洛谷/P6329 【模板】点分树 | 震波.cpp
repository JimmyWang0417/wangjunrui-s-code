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
const int N = 1e5 + 5;
int n, m, a[N];
struct Tree_array
{
    int n;
    vector<int> sum;
    inline void resize(int _n)
    {
        n = _n + 1;
        sum.resize(n + 5);
    }
    inline void update(int pos, int val)
    {
        ++pos;
        for (int i = pos; i <= n; i += lowbit(i))
            sum[i] += val;
    }
    inline int query(int pos)
    {
        ++pos;
        int res = 0;
        for (int i = min(pos, n); i > 0; i -= lowbit(i))
            res += sum[i];
        return res;
    }
} tree1[N], tree2[N];
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
int sum, root;
int size[N], maxsize[N];
vector<int> g[N];
bool vis[N];
int dis[N][25], fa[N][25], cnt[N];
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
inline void dfs(int u, int _fa, int d)
{
    size[u] = 1;
    ++cnt[u];
    dis[u][cnt[u]] = d, fa[u][cnt[u]] = root;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        dfs(v, u, d + 1);
        size[u] += size[v];
    }
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    dfs(u, 0, 0);
    vis[u] = true;
    tree1[u].resize(sum / 2), tree2[u].resize(sum);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = size[v];
        solve(v);
    }
}
inline void update(int u, int val)
{
    for (int i = cnt[u]; i > 1; --i)
    {
        tree1[fa[u][i]].update(dis[u][i], val);
        tree2[fa[u][i]].update(dis[u][i - 1], val);
    }
    tree1[fa[u][1]].update(dis[u][1], val);
}
inline int query(int u, int alldis)
{
    int ans = 0;
    for (int i = cnt[u]; i > 1; --i)
        ans += tree1[fa[u][i]].query(alldis - dis[u][i]) - tree2[fa[u][i]].query(alldis - dis[u][i - 1]);
    ans += tree1[fa[u][1]].query(alldis - dis[u][1]);
    return ans;
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
    maxsize[root = 0] = sum = n;
    solve(1);
    for (int i = 1; i <= n; ++i)
        update(i, a[i]);
    int lastans = 0;
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y;
        read(opt, x, y);
        x ^= lastans, y ^= lastans;
        if (opt == 0)
            printf("%d\n", lastans = query(x, y));
        else
        {
            update(x, y - a[x]);
            a[x] = y;
        }
    }
    return 0;
}