#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 1e6 + 5;
int n, m;
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
int fa[N][25];
int dis[N];
int dep[N];
int dfn[N], dfstime;
pair<int, int> where[N];
inline void init(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    dfn[u] = ++dfstime;
    fa[u][0] = _fa;
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        init(v, u);
        if (dis[where[u].first] < dis[v])
        {
            where[u].second = where[u].first;
            where[u].first = v;
        }
        else if (dis[where[u].second] < dis[v])
            where[u].second = v;
    }
    dis[u] = dis[where[u].first] + 1;
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
vector<int> g[N];
int f[N];
bool exist[N];
int answer;
inline void dfs(int u, int _fa, int dist)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u, max(dist + 1, where[u].first == v ? dis[where[u].second] + 2 : dis[u] + 1));
        if (!exist[v])
            ckmax(answer, dis[v] + 1);
        exist[u] |= exist[v];
        f[u] += f[v];
    }
    if (f[u] == m)
        ckmax(answer, dist);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("formation.in", "r", stdin);
    freopen("formation.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        g[x].push_back(i);
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    init(1, 0);
    for (int i = 1; i <= m; ++i)
        if (!g[i].empty())
        {
            sort(g[i].begin(), g[i].end(), [](int x, int y)
                 { return dfn[x] < dfn[y]; });
            auto nxt = g[i].begin();
            ++f[*nxt];
            int lca = *nxt;
            ++nxt;
            for (auto it = g[i].begin(); nxt != g[i].end(); ++nxt, ++it)
            {
                int nmsl = getlca(*it, *nxt);
                ++f[*nxt];
                --f[nmsl];
                lca = getlca(lca, nmsl);
            }
            exist[lca] = true;
        }
    dfs(1, 0, 0);
    printf("%d\n", answer);
    return 0;
}