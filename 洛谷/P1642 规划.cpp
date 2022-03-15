// Problem: P1642 规划
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1642
// Memory Limit: 125 MB
// Time Limit: 1000 ms
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
constexpr int N = 105;
constexpr double eps = 1e-4;
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
int n, m, a[N], b[N];
int size[N];
double dp[N][N], g[N];
inline void dfs(int u, int _fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        memcpy(g, dp[u], sizeof(dp[u]));
        memset(dp[u], -127 / 3, sizeof(dp[u]));
        for (int j = 1; j <= size[u]; ++j)
            for (int k = 0; k <= size[v]; ++k)
                ckmax(dp[u][j + k], g[j] + dp[v][k]);
        size[u] += size[v];
    }
    dp[u][0] = 0;
}
inline bool check(double mid)
{
    memset(dp, -127 / 3, sizeof(dp));
    for (int i = 1; i <= n; ++i)
        dp[i][1] = a[i] - mid * b[i];
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        if (dp[i][m] > -eps)
            return true;
    return false;
}
signed main()
{
    read(n, m);
    m = n - m;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    double l = 0, r = 1e18;
    while (r - l >= eps)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%.1lf\n", l);
    return 0;
}