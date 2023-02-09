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
const int N = 5005;
int n, deg[N];
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
int root;
int dp[N][N][2], g[N][2];
int size[N];
inline void dfs(int u, int _fa)
{
    if (deg[u] == 1)
    {
        size[u] = 1;
        dp[u][1][1] = dp[u][0][0] = 0;
        return;
    }
    dp[u][0][0] = dp[u][0][1] = 0;
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        memcpy(g, dp[u], sizeof(g));
        memset(dp[u], 0x3f, sizeof(dp[u]));
        for (int i = 0; i <= size[u]; ++i)
            for (int j = 0; j <= size[v]; ++j)
            {
                ckmin(dp[u][i + j][0], g[i][0] + min(dp[v][j][0], dp[v][j][1] + 1));
                ckmin(dp[u][i + j][1], g[i][1] + min(dp[v][j][0] + 1, dp[v][j][1]));
            }
        size[u] += size[v];
    }
}
signed main()
{
    memset(dp, 0x3f, sizeof(dp));
    read(n);
    if (n == 2)
    {
        printf("1\n");
        return 0;
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
        ++deg[u], ++deg[v];
    }
    for (int i = 1; i <= n; ++i)
        if (deg[i] > 1)
        {
            root = i;
            break;
        }
    dfs(root, 0);
    printf("%d\n", min(dp[root][size[root] >> 1][0], dp[root][size[root] >> 1][1]));
    return 0;
}