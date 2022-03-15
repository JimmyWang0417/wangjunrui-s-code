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
const int N = 105, M = 610;
template <typename T>
inline void ckmin(T &x, int y)
{
    if (x > y)
        x = y;
}
template <typename T>
inline void ckmax(T &x, int y)
{
    if (x < y)
        x = y;
}
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int st[N], top;
int dfn[N], low[N], dfstime;
int belong[N], color;
struct node
{
    int w, v, d;
} a[N];
int W[N], V[N];
inline void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!belong[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        belong[u] = ++color;
        W[color] += a[u].w;
        V[color] += a[u].v;
        while (st[top] != u)
        {
            belong[st[top]] = color;
            W[color] += a[st[top]].w;
            V[color] += a[st[top]].v;
            --top;
        }
        --top;
    }
}
int n, m;
int dp[N][M];
inline void dfs(int u)
{
    dp[u][W[u]] = V[u];
    // printf("%d %d %d\n", u, W[u], V[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
        for (int j = m; j >= 0; --j)
            for (int k = j; k >= 1; --k)
                ckmax(dp[u][j], dp[u][j - k] + dp[v][k]);
    }
}
bool vis[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i].w);
    for (int i = 1; i <= n; ++i)
        read(a[i].v);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].d);
        if (a[i].d)
            add_edge(a[i].d, i);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    memset(head, num_edge = 0, sizeof(head));
    for (int i = 1; i <= n; ++i)
    {
        if (!a[i].d || belong[a[i].d] == belong[i])
            continue;
        add_edge(belong[a[i].d], belong[i]);
        vis[belong[i]] = true;
    }
    memset(dp, ~0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= color; ++i)
        if (!vis[i])
        {
            dfs(i);
            for (int j = m; j >= 0; --j)
                for (int k = j; k >= 1; --k)
                    ckmax(dp[0][j], dp[0][j - k] + dp[i][k]);
        }
    int res = ~0x7fffffff;
    for (int i = 0; i <= m; ++i)
        ckmax(res, dp[0][i]);
    printf("%d\n", res);
    return 0;
}