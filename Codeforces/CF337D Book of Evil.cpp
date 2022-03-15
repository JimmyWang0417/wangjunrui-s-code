#pragma GCC optimize(3,Ofast)
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
const int N = 1e5 + 5;
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
int dis[N];
int where[N][2];
bool a[N];
inline void dfs(int u, int _fa)
{
    if (a[u])
        dis[u] = 0;
    else
        dis[u] = INT_MIN;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        if (dis[where[u][0]] < dis[v])
        {
            where[u][1] = where[u][0];
            where[u][0] = v;
        }
        else if (dis[where[u][1]] < dis[v])
            where[u][1] = v;
    }
    if (where[u][0])
        dis[u] = dis[where[u][0]] + 1;
    // printf(" %d %d %d %d %d\n",u,where[u][0],where[u][1],dis[where[u][0]],dis[where[u][1]]);
}
int alldis[N];
inline void dfs(int u, int _fa, int maxx)
{
    alldis[u] = max(dis[u], maxx);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        int res = a[u]?0:INT_MIN;
        if (where[u][0] == v)
        {
            if (where[u][1])
                res = dis[where[u][1]] + 1;
        }
        else
        if(where[u][0])
            res = dis[where[u][0]] + 1;
        dfs(v, u, max(maxx, res) + 1);
    }
}
int n, m, d;
signed main()
{
    read(n, m, d);
    for (int i = 1; i <= m; ++i)
    {
        int x;
        read(x);
        a[x] = true;
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dis[0] = INT_MIN;
    dfs(1, 0);
    dfs(1, 0, INT_MIN);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (alldis[i] <= d)
            ++ans;
    printf("%d\n", ans);
    return 0;
}