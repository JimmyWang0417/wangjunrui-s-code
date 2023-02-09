#include <bits/stdc++.h>
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
const int N = 2e5 + 5, M = 1005;
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
int n, m, q;
bool used[N];
struct node
{
    int u, v, w;
} e[N];
ll dis[N];
int dep[N];
int fa[N][25];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    fa[u][0] = _fa;
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (dep[v])
            continue;
        dis[v] = dis[u] + edge[i].dis;
        used[(i + 1) >> 1] = true;
        dfs(v, u);
    }
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
#define getdis(u, v) (dis[u] + dis[v] - 2 * dis[getlca(u, v)])
int p[N], tot;
ll dist[M][M];
#define calc(v) ((int)(lower_bound(p + 1, p + 1 + tot, v) - p))
ll predis[105][N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        read(e[i].u, e[i].v, e[i].w);
        //		printf("  %d %d %d\n",e[i].u,e[i].v,e[i].w);
        add_edge(e[i].u, e[i].v, e[i].w);
        add_edge(e[i].v, e[i].u, e[i].w);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; ++i)
        if (!used[i])
        {
            p[++tot] = e[i].u;
            p[++tot] = e[i].v;
        }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - 1 - p);
    for (int i = 1; i <= tot; ++i)
        for (int j = 1; j <= tot; ++j)
            dist[i][j] = getdis(p[i], p[j]);
    for (int i = 1; i <= m; ++i)
    {
        if (used[i])
            continue;
        int u = calc(e[i].u), v = calc(e[i].v), w = e[i].w;
        dist[u][v] = min(dist[u][v], (ll)w);
        dist[v][u] = min(dist[v][u], (ll)w);
    }
    for (int k = 1; k <= tot; ++k)
        for (int i = 1; i <= tot; ++i)
            for (int j = 1; j <= tot; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for (int i = 1; i <= tot; ++i)
        for (int j = 1; j <= n; ++j)
            predis[i][j] = getdis(p[i], j);
    read(q);
    while (q--)
    {
        int u, v;
        read(u, v);
        ll res = getdis(u, v);
        for (int i = 1; i <= tot; ++i)
            for (int j = i + 1; j <= tot; ++j)
            {
                res = min(res, min(predis[i][u] + dist[i][j] + predis[j][v],
                                   predis[j][u] + dist[j][i] + predis[i][v]));
            }
        printf("%lld\n", res);
    }
    return 0;
}
