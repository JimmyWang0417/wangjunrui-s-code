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
using namespace std;
const int N = 1e6 + 5;
int n, a[N];
bool vis[N];
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
int dfn[N], dfstime;
int fa[N];
int b[N], tot;
inline void dfs(int u, int _fa)
{
    fa[u] = _fa;
    dfn[u] = ++dfstime;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        if (!dfn[v])
            dfs(v, u);
        else
        {
            if (dfn[u] < dfn[v])
            {
                int x = v;
                while (x != u)
                {
                    vis[b[++tot] = x] = true;
                    x = fa[x];
                }
                vis[b[++tot] = u] = true;
            }
        }
    }
}
ll dp[N][2];
inline void solve(int u, int _fa)
{
    dp[u][1] = a[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        solve(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}
ll f[N][2];
inline ll work(int root)
{
    tot = 0;
    dfs(root, 0);
    for (int i = 1; i <= tot; ++i)
        solve(b[i], 0);
    f[1][0] = 0;
    f[1][1] = dp[b[1]][1];
    for (int i = 2; i <= tot; ++i)
    {
        f[i][0] = max(f[i - 1][0], f[i - 1][1]) + dp[b[i]][0];
        f[i][1] = f[i - 1][0] + dp[b[i]][1];
    }
    ll res = f[tot][0];
    f[1][0] = dp[b[1]][0];
    f[1][1] = 0;
    for (int i = 2; i <= tot; ++i)
    {
        f[i][0] = max(f[i - 1][0], f[i - 1][1]) + dp[b[i]][0];
        f[i][1] = f[i - 1][0] + dp[b[i]][1];
    }
    return max(res, max(f[tot][0], f[tot][1]));
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int _fa;
        read(a[i], _fa);
        add_edge(_fa, i);
        add_edge(i, _fa);
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            ans += work(i);
    printf("%lld\n", ans);
    return 0;
}