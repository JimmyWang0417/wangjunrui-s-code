/**
 *    unicode: UTF-8
 *    name:    CF827D Best Edge Weight
 *    author:  wangjunrui
 *    created: 2022.06.30 周四 11:12:39 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <numeric>
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
constexpr int N = 2e5 + 5;
int n, m;
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
int dep[N], Log[N];
int f[N][20], g[N][20];
inline void dfs(int u)
{
    dep[u] = dep[f[u][0]] + 1;
    for (int i = 0; i < Log[dep[u]]; ++i)
    {
        f[u][i + 1] = f[f[u][i]][i];
        g[u][i + 1] = max(g[u][i], g[f[u][i]][i]);
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == f[u][0])
            continue;
        f[v][0] = u;
        g[v][0] = edge[i].dis;
        dfs(v);
    }
}
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
inline int getmax(int u, int v)
{
    int res = 0;
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (dep[f[u][i]] >= dep[v])
        {
            ckmax(res, g[u][i]);
            u = f[u][i];
        }
    if (u == v)
        return res;
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (f[u][i] != f[v][i])
        {
            ckmax(res, max(g[u][i], g[v][i]));
            u = f[u][i];
            v = f[v][i];
        }
    return max(res, max(g[u][0], g[v][0]));
}
int answer[N];
struct node
{
    int u, v, w, id;
    inline bool operator<(const node &rhs) const
    {
        return w < rhs.w;
    }
} a[N];
bool vis[N];
int fa[N], b[N];
inline int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
signed main()
{
    read(n, m);
    if (m == n - 1)
    {
        for (int i = 1; i <= m; ++i)
            printf("-1 ");
        putchar('\n');
        return 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        read(a[i].u, a[i].v, a[i].w);
        a[i].id = i;
    }
    sort(a + 1, a + 1 + m);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
        Log[i] = Log[i >> 1] + 1;
    iota(fa + 1, fa + 1 + n, 1);
    for (int i = 1; i <= m; ++i)
    {
        int u = find(a[i].u), v = find(a[i].v);
        if (u == v)
            continue;
        fa[u] = v;
        add_edge(a[i].u, a[i].v, a[i].w);
        add_edge(a[i].v, a[i].u, a[i].w);
        vis[i] = true;
    }
    dfs(1);
    iota(fa + 1, fa + 1 + n, 1);
    for (int i = 1; i <= m; ++i)
    {
        if (vis[i])
            continue;
        int u = a[i].u, v = a[i].v, w = a[i].w, lca = getlca(u, v);
        while (dep[u = find(u)] > dep[lca])
        {
            b[u] = w;
            fa[u] = f[u][0];
        }
        while (dep[v = find(v)] > dep[lca])
        {
            b[v] = w;
            fa[v] = f[v][0];
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        int u = a[i].u, v = a[i].v;
        if (vis[i])
        {
            if (dep[u] > dep[v])
                swap(u, v);
            answer[a[i].id] = b[v];
        }
        else
            answer[a[i].id] = getmax(u, v);
    }
    for (int i = 1; i <= m; ++i)
        printf("%d ", answer[i] - 1);
    putchar('\n');
    return 0;
}