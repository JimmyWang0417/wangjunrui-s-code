#include <bits/stdc++.h>
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
constexpr int N = 1005;
constexpr int mod = 1e9 + 7;
int n, k;
ll dp[N][N * 5][6], g[N * 5][6];
int maxx[N];
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
inline void dfs(int u, int _fa)
{
    for (int i = 1; i <= k; ++i)
        dp[u][0][i] = 1;
    maxx[u] = 0;
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        memset(g, 0, sizeof(g));
        for (int i = 0; i <= maxx[u]; ++i)
            for (int j = 0; j <= k; ++j)
                if (dp[u][i][j])
                    for (int l = 0; l <= maxx[v]; ++l)
                        for (int r = 0; r <= k; ++r)
                            if (dp[v][l][r])
                            {
                                (g[i + l + r][max(j - r, 0)] += dp[u][i][j] * dp[v][l][r]) %= mod;
                                ckmax(maxx[u], i + l + r);
                            }
        memcpy(dp[u], g, sizeof(g));
    }
}
signed main()
{
    read(n, k);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n * k; ++i)
    {
        ll res = 0;
        for (int j = max(i - k, 0); j <= i; ++j)
            (res += dp[1][j][i - j]) %= mod;
        printf("%lld\n", res);
    }
    return 0;
}