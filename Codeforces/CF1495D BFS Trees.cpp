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
constexpr int N = 400 + 5, M = 600 + 5;
constexpr int mod = 998244353;
int n, m;
struct Edge
{
    int next, to;
} edge[M * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int dis[N][N], cnt[N][N];
bool vis[N];
inline void bfs(int S)
{
    queue<int> q;
    q.push(S);
    vis[S] = true;
    cnt[S][S] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (vis[v])
            {
                if (dis[S][v] == dis[S][u] + 1)
                    cnt[S][v] = min(cnt[S][v] + cnt[S][u], 2);
                continue;
            }
            vis[v] = true;
            dis[S][v] = dis[S][u] + 1;
            cnt[S][v] = cnt[S][u];
            q.push(v);
        }
    }
    memset(vis, 0, sizeof(vis));
}
inline ll calc(int x, int y)
{
    ll res = 1;
    for (int u = 1; u <= n; ++u)
    {
        if (dis[x][u] + dis[u][y] == dis[x][y])
            continue;
        int sum = 0;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[x][u] == dis[x][v] + 1 && dis[y][u] == dis[y][v] + 1)
                ++sum;
        }
        (res *= sum) %= mod;
    }
    return res;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n; ++i)
        bfs(i);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (cnt[i][j] == 2)
            {
                printf("0 ");
                continue;
            }
            printf("%lld ", calc(i, j));
        }
        putchar('\n');
    }
    return 0;
}