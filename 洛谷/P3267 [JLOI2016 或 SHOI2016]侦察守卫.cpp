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
const int N = 5e5 + 5;
int n, m, d, a[N];
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
int f[N][25], g[N][25];
inline void dfs(int u, int _fa)
{
    for (int i = 1; i <= d; ++i)
        f[u][i] = a[u];
    f[u][d + 1] = 0x3f3f3f3f;
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        for (int i = 0; i <= d; ++i)
            f[u][i] = min(f[u][i] + g[v][i], g[u][i + 1] + f[v][i + 1]);
        for (int i = d - 1; i >= 0; --i)
            ckmin(f[u][i], f[u][i + 1]);
        g[u][0] = f[u][0];
        for (int i = 1; i <= d; ++i)
            g[u][i] += g[v][i - 1];
        for (int i = 1; i <= d + 1; ++i)
            ckmin(g[u][i], g[u][i - 1]);
    }
}
signed main()
{
    read(n, d);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x;
        read(x);
        f[x][0] = g[x][0] = a[x];
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    printf("%d\n", g[1][0]);
    return 0;
}