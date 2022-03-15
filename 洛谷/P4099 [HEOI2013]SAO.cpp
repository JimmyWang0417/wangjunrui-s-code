#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 1005;
const int mod = 1e9 + 7;
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
int n;
int C[N][N];
ll dp[N][N], g[N];
int size[N];
inline void dfs(int u, int _fa)
{
    size[u] = 1;
    dp[u][1] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        memcpy(g, dp[u], sizeof(dp[u]));
        memset(dp[u], 0, sizeof(dp[u]));
        if (edge[i].dis)
        {
            for (int x = 1; x <= size[u]; ++x)
                for (int y = x; y < x + size[v]; ++y)
                    (dp[u][y] += g[x] * (dp[v][size[v]] - dp[v][y - x]) % mod * C[size[u] + size[v] - y][size[u] - x] % mod * C[y - 1][x - 1] % mod) %= mod;
        }
        else
        {
            for (int x = 1; x <= size[u]; ++x)
                for (int y = x + 1; y <= x + size[v]; ++y)
                    (dp[u][y] += g[x] * dp[v][y - x] % mod * C[size[u] + size[v] - y][size[u] - x] % mod * C[y - 1][x - 1] % mod) %= mod;
        }
        size[u] += size[v];
    }
    for (int i = 2; i <= size[u]; ++i)
        (dp[u][i] += dp[u][i - 1]) %= mod;
}
inline void work()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        char opt[10];
        scanf("%d%s%d", &u, opt, &v);
        add_edge(u, v, opt[0] == '<');
        add_edge(v, u, opt[0] == '>');
    }
    memset(dp, 0, sizeof(dp));
    dfs(0, 0);
    printf("%lld\n", (dp[0][size[0]] + mod) % mod);
    memset(head, num_edge = 0, sizeof(head));
}
signed main()
{
    for (int i = C[0][0] = 1; i <= 1000; ++i)
    {
        for (int j = C[i][0] = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}