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
const int N = 2e6 + 5;
struct Edge
{
    int next, to, dis;
} edge[N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int dfn[N], dfstime;
int lasedge[N], fa[N];
int st[N], top;
bool vis[N];
inline void dfs(int u, int las)
{
    dfn[u] = ++dfstime;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (i == (las ^ 1))
            continue;
        if (!dfn[v])
        {
            lasedge[v] = edge[i].dis;
            fa[v] = u;
            dfs(v, i);
        }
        else if (dfn[v] < dfn[u])
        {
            lasedge[v] = edge[i].dis;
            st[++top] = u;
            vis[u] = true;
            int x = u;
            while (x != v)
            {
                x = fa[x];
                vis[x] = true;
                st[++top] = x;
            }
        }
    }
}
ll dis[N], nxtdis[N];
ll answer;
inline void calc(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        calc(v, u);
        ll res = dis[v] + edge[i].dis;
        if (res > dis[u])
        {
            nxtdis[u] = dis[u];
            dis[u] = res;
        }
        else if (res > nxtdis[u])
            nxtdis[u] = res;
    }
    ckmax(answer, dis[u] + nxtdis[u]);
}
ll dist[N];
int q[N];
ll g[N];
inline void solve()
{
    for (int i = 1; i <= top; ++i)
        calc(st[i], 0);
    for (int i = 1; i <= top; ++i)
        dist[i + 1] = dist[i] + lasedge[st[i]];
    for (int i = 1; i < top; ++i)
        dist[i + top + 1] = dist[i + top] + lasedge[st[i]];
    int first = 1, second = 0;
    for (int i = 1; i <= top; ++i)
    {
        if (first <= second)
            ckmax(answer, g[first] + dis[st[i]] + dist[i]);
        while (first <= second && g[second] < dis[st[i]] - dist[i])
            --second;
        q[++second] = i;
        g[second] = dis[st[i]] - dist[i];
    }
    for (int i = 1; i < top; ++i)
    {
        while (first <= second && q[first] <= i)
            ++first;
        if (first <= second)
            ckmax(answer, g[first] + dis[st[i]] + dist[i + top]);
        while (first <= second && dis[st[q[second]]] - dist[q[second]] < dis[st[i]] - dist[i + top])
            --second;
        q[++second] = i + top;
        g[second] = dis[st[i]] - dist[i + top];
    }
}
int n;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(i, u, v);
        add_edge(u, i, v);
    }
    ll res = 0;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
        {
            dfs(i, 0);
            solve();
            res += answer;
            answer = 0;
            top = 0;
        }
    printf("%lld\n", res);
    return 0;
}