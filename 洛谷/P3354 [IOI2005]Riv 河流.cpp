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
const int N = 105;
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
int n, m;
int dp[N][N][55];
int g[N][55];
int a[N];
int fa[N];
int father[N], tot;
int dis[N];
inline void dfs(int u)
{
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        dis[v] = dis[u] + edge[e].dis;
        dfs(v);
    }
    tot = 0;
    for (int x = u;; x = fa[x])
    {
        father[++tot] = x;
        if (!x)
            break;
    }
    dp[u][u][1] = 0;
    for (int i = 2; i <= tot; ++i)
        dp[u][father[i]][0] = a[u] * (dis[u] - dis[father[i]]);
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        for (int i = 1; i <= tot; ++i)
        {
            for (int j = m; j >= 0; --j)
            {
                dp[u][father[i]][j] += min(dp[v][father[i]][0], dp[v][v][0]);
                for (int k = j; k >= 0; --k)
                    ckmin(dp[u][father[i]][j], dp[u][father[i]][j - k] + min(dp[v][father[i]][k], dp[v][v][k]));
            }
        }
    }
}
signed main()
{
    read(n, m);
    ++m;
    for (int i = 1; i <= n; ++i)
    {
        int w;
        read(a[i], fa[i], w);
        add_edge(fa[i], i, w);
    }
    memset(dp, 0x3f, sizeof(dp));
    dfs(0);
    printf("%d\n", dp[0][0][m]);
    return 0;
}