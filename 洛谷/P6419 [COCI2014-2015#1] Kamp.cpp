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
const int N = 5e5 + 5;
int n, m;
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
ll dp[N], dis[N];
ll add[N][2];
int where[N][2];
int size[N];
inline void dfs(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        if (!size[v])
            continue;
        dp[u] += dp[v] + edge[i].dis;
        ll res = dis[v] + edge[i].dis;
        if (res > add[u][0])
        {
            where[u][1] = where[u][0], where[u][0] = v;
            add[u][1] = add[u][0], add[u][0] = res;
        }
        else if (res > add[u][1])
        {
            where[u][1] = v;
            add[u][1] = res;
        }
        size[u] += size[v];
    }
    dis[u] = add[u][0];
}
inline void solve(int u, int _fa, int lasedge)
{
    if (_fa && size[1] - size[u] > 0)
    {
        ll res = lasedge + ((where[_fa][0] == u) ? add[_fa][1] : add[_fa][0]);
        if (res > add[u][0])
        {
            where[u][1] = where[u][0], where[u][0] = _fa;
            add[u][1] = add[u][0], add[u][0] = res;
        }
        else if (res > add[u][1])
        {
            where[u][1] = _fa;
            add[u][1] = res;
        }
        dp[u] += (size[u] ? dp[_fa] - dp[u] : dp[_fa] + lasedge);
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        solve(v, u, edge[i].dis);
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i <= m; ++i)
    {
        int x;
        read(x);
        ++size[x];
    }
    dfs(1, 0);
    solve(1, 0, 0);
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", dp[i] * 2 - add[i][0]);
    return 0;
}