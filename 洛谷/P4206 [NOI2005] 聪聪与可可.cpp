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
const int N = 1005;
int n, m;
int C, M;
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
int dis[N][N], pre[N][N];
bool vis[N][N];
int q[N];
inline void bfs(int S)
{
    int tail;
    q[tail = 1] = S;
    vis[S][S] = true;
    pre[S][S] = S;
    for (int now = 1; now <= tail; ++now)
    {
        int u = q[now];
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (!vis[S][v])
            {
                dis[S][v] = dis[S][u] + 1;
                pre[S][v] = u;
                vis[S][v] = true;
                q[++tail] = v;
            }
            else if (dis[S][v] == dis[S][u] + 1 && pre[S][v] > u)
                pre[S][v] = u;
        }
    }
    memset(vis[S] + 1, 0, n * sizeof(int));
}
int deg[N];
double dp[N][N];
inline double dfs(int x, int y)
{
    if (x == y)
        return 0;
    if (dis[x][y] <= 2)
        return 1;
    if (vis[x][y])
        return dp[x][y];
    vis[x][y] = true;
    double &res = dp[x][y];
    int u = pre[y][pre[y][x]];
    for (int i = head[y]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        res += dfs(u, v);
    }
    res += dfs(u, y);
    res /= deg[y] + 1;
    ++res;
    return res;
}
signed main()
{
    read(n, m, C, M);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
        ++deg[u], ++deg[v];
    }
    for (int i = 1; i <= n; ++i)
        bfs(i);
    printf("%.3lf\n", dfs(C, M));
    return 0;
}