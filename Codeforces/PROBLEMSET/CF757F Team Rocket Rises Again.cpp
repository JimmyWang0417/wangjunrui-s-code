/**
 *    unicode: UTF-8
 *    name:    CF757F Team Rocket Rises Again
 *    author:  whitepaperdog
 *    created: 2022.06.30 周四 13:02:19 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>
#include <vector>
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
constexpr int N = 2e5 + 5, M = 3e5 + 5;
int n, m;
struct Edge
{
    int next, to, dis;
} edge[M * 2];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
bool vis[N];
int p[N], tot;
ll dis[N];
inline void dijkstra(int S)
{
    __gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>> q;
    memset(dis, 0x3f, sizeof(dis));
    q.push(make_pair(dis[S] = 0, S));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        p[++tot] = u;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
                q.push(make_pair(dis[v] = dis[u] + edge[i].dis, v));
        }
    }
}
vector<int> g[N];
int dep[N], fa[N][20];
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 17; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 17; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
int size[N];
inline void dfs(int u, int _fa)
{
    size[u] = 1;
    for (int v : g[u])
    {
        if (v == _fa)
            continue;
        dfs(v, u);
        size[u] += size[v];
    }
}
signed main()
{
    int s;
    read(n, m, s);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dijkstra(s);
    for (int qwq = 1; qwq <= tot; ++qwq)
    {
        int u = p[qwq];
        int lca = 0;
        for (int e = head[u]; e; e = edge[e].next)
        {
            int &v = edge[e].to;
            if (dis[v] + edge[e].dis == dis[u])
            {
                if (!lca)
                    lca = v;
                else
                    lca = getlca(lca, v);
            }
        }
        dep[u] = dep[lca] + 1;
        g[fa[u][0] = lca].push_back(u);
        for (int i = 0; i < 17; ++i)
            fa[u][i + 1] = fa[fa[u][i]][i];
    }
    dfs(s, 0);
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i == s)
            continue;
        ckmax(res, size[i]);
    }
    printf("%d\n", res);
    return 0;
}