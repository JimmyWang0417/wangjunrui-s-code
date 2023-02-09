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
constexpr int N = 5005;
int n, m;
ll dp[N][N][2], g[N][2];
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int a[N], b[N];
int size[N];
inline void dfs(int u)
{
    dp[u][0][0] = 0, dp[u][1][0] = a[u];
    dp[u][1][1] = a[u] - b[u];
    size[u] = 1;
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        dfs(v);
        memcpy(g, dp[u], sizeof(g));
        memset(dp[u], 0x3f, sizeof(dp[u]));
        for (int i = 0; i <= size[u]; ++i)
            for (int j = 0; j <= size[v]; ++j)
            {
                ckmin(dp[u][i + j][0], g[i][0] + dp[v][j][0]);
                ckmin(dp[u][i + j][1], g[i][1] + min(dp[v][j][0], dp[v][j][1]));
            }
        size[u] += size[v];
    }
}
signed main()
{
    read(n, m, a[1], b[1]);
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        read(a[i], b[i], fa);
        add_edge(fa, i);
    }
    memset(dp, 0x3f, sizeof(dp));
    dfs(1);
    for (int i = n; i >= 1; --i)
    {
        if (dp[1][i][0] <= m || dp[1][i][1] <= m)
        {
            printf("%d\n", i);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}