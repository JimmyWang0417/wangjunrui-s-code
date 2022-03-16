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
constexpr int N = 2e5 + 5;
constexpr int mod = 998244353;
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
int n, a[N];
double f[N][2];
ll g[N][2];
inline void dfs(int u, int _fa)
{
    f[u][0] = 0, g[u][0] = 1;
    f[u][1] = log(a[u]), g[u][1] = a[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        double f0 = f[u][0], f1 = f[u][1];
        ll g0 = g[u][0], g1 = g[u][1];
        f[u][0] = f[u][1] = 0;
        f[u][0] = f0 + f[v][0], g[u][0] = g0 * g[v][0] % mod;
        f[u][1] = f1 + f[v][0], g[u][1] = g1 * g[v][0] % mod;
        if (f[u][0] < f0 + f[v][1])
            f[u][0] = f0 + f[v][1], g[u][0] = g0 * g[v][1] % mod;
    }
}
signed main()
{
    freopen("doubt.in", "r", stdin);
    freopen("doubt.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    printf("%lld\n", f[1][0] > f[1][1] ? g[1][0] : g[1][1]);
    return 0;
}
