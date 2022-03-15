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
const int N = 1e6 + 5;
int n, q;
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
bool vis[N];
int sum, size[N], maxsize[N], root;
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
int sumd[N];
ll alldis[N];
inline void dfs(int u, int _fa, int d)
{
    size[u] = 1;
    ++cnt[u];
    fa[u][cnt[u]] = root, dis[u][cnt[u]] = d;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        dfs(v, u, d + edge[i].dis);
        size[u] += size[v];
    }
}
vector<pair<int, int>> g[N];
inline int solve(int u)
{
    getroot(u, 0);
    u = root;
    root = u;
    dfs(u, 0, 0);
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = size[v];
        g[u].push_back(make_pair(v, solve(v)));
    }
    return u;
}
inline void update(int u, int val)
{
    for (int i = cnt[u]; i > 1; --i)
    {
        alldis[fa[u][i]] += (ll)val * (dis[u][i] - dis[u][i - 1]);
        sumd[fa[u][i]] += val;
    }
    alldis[fa[u][1]] += (ll)val * dis[u][1];
    sumd[fa[u][1]] += val;
}
inline ll calc(int u)
{
    ll res = 0;
    for (int i = cnt[u]; i >= 1; --i)
        res += alldis[fa[u][i]];
    for (int i = 1; i < cnt[u]; ++i)
        res += (ll)(sumd[fa[u][i]] - sumd[fa[u][i + 1]]) * dis[u][i];
    return res;
}
inline ll query(int u)
{
    ll ans = calc(u);
    for (auto v : g[u])
    {
        ll res = calc(v.first);
        if (res < ans)
            return query(v.second);
    }
    return ans;
}
signed main()
{
    read(n, q);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    maxsize[root = 0] = sum = n;
    root = solve(1);
    while (q--)
    {
        int x, y;
        read(x, y);
        update(x, y);
        printf("%lld\n", query(root));
    }
    return 0;
}