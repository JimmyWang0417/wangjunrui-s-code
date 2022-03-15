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
const int N = 3e5 + 5;
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
int root;
int dis[N];
inline void dfs1(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dis[v] = dis[u] + edge[i].dis;
        dfs1(v, u);
    }
}
int nxt[N], nxtdis[N], e[N];
inline void dfs2(int u, int _fa)
{
    dis[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs2(v, u);
        int res = dis[v] + edge[i].dis;
        if (res > dis[u])
        {
            nxtdis[u] = dis[u];
            dis[u] = res;
            e[u] = edge[i].dis;
            nxt[u] = v;
        }
        else if (res > nxtdis[u])
            nxtdis[u] = res;
    }
}
int q[N];
#define head nmsl
inline int solve()
{
    int ans = 0x7fffffff;
    for (int u = root, v = root, sum = 0, las = nxtdis[v], now = 0; u; u = nxt[u])
    {
        now = max(now, nxtdis[u]);
        while (sum > m)
        {
            las += e[v];
            sum -= e[v];
            v = nxt[v];
            las = max(las, nxtdis[v]);
        }
        ans = min(ans, max(now, max(dis[u], las)));
        sum += e[u];
    }
    return ans;
}
#undef head
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
    dfs1(1, 0);
    root = 1;
    for (int i = 2; i <= n; ++i)
        if (dis[i] > dis[root])
            root = i;
    dfs2(root, 0);
    printf("%d\n", solve());
    return 0;
}