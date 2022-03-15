// Problem: F. Cheap Robot
// Contest: Codeforces - Codeforces Round #600 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1253/F
// Memory Limit: 512 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 6e5 + 5;
int n, k, m;
struct Edge
{
    int next, to, dis;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
ll dis[N];
__gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>>::point_iterator its[N];
inline void dijkstra()
{
    __gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>> q;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= k; ++i)
        q.push(make_pair(dis[i] = 0, i));
    for (int i = k + 1; i <= n; ++i)
        its[i] = q.push(make_pair(dis[i], i));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
                q.modify(its[v], make_pair(dis[v] = dis[u] + edge[i].dis, v));
        }
    }
}
struct node
{
    int u, v;
    ll w;
    inline bool operator<(const node &rhs) const
    {
        return w < rhs.w;
    }
} a[N];
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
int f[N][25];
int dep[N];
vector<int> g[N];
ll w[N];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    f[u][0] = _fa;
    for (int i = 0; i < 20; ++i)
        f[u][i + 1] = f[f[u][i]][i];
    for (auto v : g[u])
    {
        f[v][0] = u;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; --i)
        if (dep[f[u][i]] >= dep[v])
            u = f[u][i];
    if (u == v)
        return u;
    for (int i = 20; i >= 0; --i)
        if (f[u][i] != f[v][i])
        {
            u = f[u][i];
            v = f[v][i];
        }
    return f[u][0];
}
signed main()
{
    int q;
    read(n, m, k, q);
    for (int i = 1; i <= m; ++i)
    {
        int w;
        read(a[i].u, a[i].v, w);
        add_edge(a[i].u, a[i].v, w);
        add_edge(a[i].v, a[i].u, w);
        a[i].w = w;
    }
    dijkstra();
    for (int i = 1; i <= m; ++i)
        a[i].w += dis[a[i].u] + dis[a[i].v];
    sort(a + 1, a + 1 + m);
    int root = 0;
    int cnt = n;
    for (int i = 1; i <= m; ++i)
    {
        int u = find(a[i].u), v = find(a[i].v);
        if (u == v)
            continue;
        ++cnt;
        g[cnt].push_back(u), g[cnt].push_back(v);
        w[cnt] = a[i].w;
        root = fa[u] = fa[v] = cnt;
    }
    dfs(root, 0);
    while (q--)
    {
        int u, v;
        read(u, v);
        printf("%lld\n", w[getlca(u, v)]);
    }
    return 0;
}