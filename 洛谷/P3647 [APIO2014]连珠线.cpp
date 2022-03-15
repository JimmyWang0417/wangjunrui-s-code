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
const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;
int n;
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
int dp[N][2];
int where[N][2], add[N][2];
inline void dfs(int u, int _fa)
{
    dp[u][0] = 0;
    add[u][0] = add[u][1] = dp[u][1] = -INF;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        int res = max(dp[v][0], dp[v][1] + edge[i].dis);
        dp[u][0] += res;
        res = dp[v][0] + edge[i].dis - res;
        if (add[u][0] < res)
        {
            add[u][1] = add[u][0], where[u][1] = where[u][0];
            add[u][0] = res, where[u][0] = v;
        }
        else if (add[u][1] < res)
            add[u][1] = res, where[u][1] = v;
    }
    dp[u][1] = dp[u][0] + add[u][0];
}
inline void solve(int u, int _fa, int lasedge)
{
    if (_fa)
    {
        int dp0 = dp[_fa][0] - max(dp[u][0], dp[u][1] + lasedge);
        int dp1 = dp0 + (where[_fa][0] == u ? add[_fa][1] : add[_fa][0]);
        int res = dp0 + lasedge - max(dp0, dp1 + lasedge);
        dp[u][0] += max(dp0, dp1 + lasedge);
        if (add[u][0] < res)
        {
            add[u][1] = add[u][0], where[u][1] = where[u][0];
            add[u][0] = res, where[u][0] = _fa;
        }
        else if (add[u][1] < res)
            add[u][1] = res, where[u][1] = _fa;
        dp[u][1] = dp[u][0] + add[u][0];
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
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dfs(1, 0);
    solve(1, 0, 0);
    int res = 0;
    for (int i = 1; i <= n; ++i)
        ckmax(res, dp[i][0]);
    printf("%d\n", res);
    return 0;
}