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
inline void dfs(int u)
{
    size[u] = 1;
    dp[u][1] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
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
char str[N];
inline void work()
{
    read(n);
    scanf("%s", str + 2);
    for (int i = 2; i <= n; ++i)
        add_edge(i >> 1, i, str[i] == '<');
    memset(dp, 0, sizeof(dp));
    dfs(1);
    printf("%lld\n", (dp[1][size[1]] + mod) % mod);
    memset(head, num_edge = 0, sizeof(head));
}
signed main()
{
    for (int i = C[0][0] = 1; i <= 1000; ++i)
    {
        for (int j = C[i][0] = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    work();
    return 0;
}