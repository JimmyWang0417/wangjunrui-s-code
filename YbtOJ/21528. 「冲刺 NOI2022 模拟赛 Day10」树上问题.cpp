#include <algorithm>
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
constexpr int N = 2e5 + 5;
int n, m;
struct Edge
{
    int next, to, dis;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int size[N], maxsize[N], sum, root;
bool vis[N];
inline void getroot(int u, int _fa)
{
    size[u] = 1;
    maxsize[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        getroot(v, u);
        size[u] += size[v];
        ckmax(maxsize[u], size[v]);
    }
    ckmax(maxsize[u], sum - size[u]);
    if (maxsize[root] > maxsize[u])
        root = u;
}
int fa[N][25], dist[N][25], cnt[N];
vector<int> tree1[N], tree2[N];
inline void dfs(int u, int _fa, int dis = 0)
{
    size[u] = 1;
    ++cnt[u];
    fa[u][cnt[u]] = root;
    dist[u][cnt[u]] = dis;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        dfs(v, u, dis + 1);
        size[u] += size[v];
    }
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    dfs(u, 0);
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
int f[N][25], dep[N], Log[N];
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (dep[f[u][i]] >= dep[v])
            u = f[u][i];
    if (u == v)
        return u;
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (f[u][i] != f[v][i])
        {
            u = f[u][i];
            v = f[v][i];
        }
    return f[u][0];
}
inline int ancestor(int u, int k)
{
    for (int i = Log[k]; i >= 0; --i)
        if ((k >> i) & 1)
            u = f[u][i];
    return u;
}
inline int getdis(int u, int v)
{
    return dep[u] + dep[v] - 2 * dep[getlca(u, v)];
}
inline void init(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    f[u][0] = _fa;
    for (int i = 0; i < Log[dep[u]]; ++i)
        f[u][i + 1] = f[f[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        init(v, u);
    }
}
inline int calc(const vector<int> &nmsl, int wdnmd)
{
    return upper_bound(nmsl.begin(), nmsl.end(), wdnmd) - nmsl.begin();
}
inline int calc(int u, int dis)
{
    int res = calc(tree1[fa[u][1]], dis - dist[u][1]);
    for (int i = 2; i <= cnt[u]; ++i)
        res += calc(tree1[fa[u][i]], dis - dist[u][i]) - calc(tree2[fa[u][i]], dis - dist[u][i - 1]);
    return res;
}
signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, i + n);
        add_edge(i + n, u);
        add_edge(v, i + n);
        add_edge(i + n, v);
    }
    int tot = 2 * n - 1;
    Log[0] = -1;
    for (int i = 1; i <= tot; ++i)
        Log[i] = Log[i >> 1] + 1;
    init(1, 0);
    maxsize[root = 0] = sum = tot;
    solve(1);
    for (int i = 1; i <= n; ++i)
    {
        tree1[fa[i][1]].push_back(dist[i][1]);
        for (int j = 2; j <= cnt[i]; ++j)
        {
            tree1[fa[i][j]].push_back(dist[i][j]);
            tree2[fa[i][j]].push_back(dist[i][j - 1]);
        }
    }
    for (int i = 1; i <= tot; ++i)
    {
        sort(tree1[i].begin(), tree1[i].end());
        sort(tree2[i].begin(), tree2[i].end());
    }
    int lastans = 0;
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        u = (u + lastans) % n + 1, v = (v + lastans) % n + 1, w = (w + lastans) % n;
        w *= 2;
        int dis = getdis(u, v);
        if (dep[u] < dep[v])
            swap(u, v);
        // printf("%d %d %d %d %d %d %d\n", u, v, w, ancestor(u, dis / 2), calc(u, w), calc(v, w), calc(ancestor(u, dis / 2), w - dis / 2));
        printf("%d\n", lastans = calc(u, w) + calc(v, w) - calc(ancestor(u, dis / 2), w - dis / 2));
    }
    return 0;
}
