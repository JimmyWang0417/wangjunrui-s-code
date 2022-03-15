#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
template <typename T>
inline void read(T &x)
{
    x = 0;
    static char s = (char)getchar();
    static bool f = false;
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
int n, d, a[N];
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
int p[N], tot;
int path[N];
int f[N], g[N];
inline void dfs(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        path[v] = edge[i].dis;
        dfs(v, u);
    }
    tot = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        p[++tot] = v;
    }
    sort(p + 1, p + 1 + tot, [](const int &x, const int &y)
         { return f[x] + path[x] > f[y] + path[y]; });
    for (int i = 1; i < a[u] && i <= tot; ++i)
        f[u] += path[p[i]] + f[p[i]];
    if (a[u] - 1 > tot)
        g[u] = f[u];
    else if (a[u] == 1)
        g[u] = -0x3f3f3f;
    else
    {
        int res = g[u] = f[u] - (path[p[a[u] - 1]] + f[p[a[u] - 1]]);
        if (a[u] > 1)
            for (int i = a[u]; i <= tot; ++i)
                ckmax(g[u], res + path[p[i]] + g[p[i]]);
        for (int i = 1; i < a[u]; ++i)
            ckmax(g[u], f[u] - f[p[i]] + g[p[i]]);
    }
}
signed main()
{
    read(n, d);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    ++a[d];
    dfs(d, 0);
    printf("%d\n", g[d]);
    return 0;
}