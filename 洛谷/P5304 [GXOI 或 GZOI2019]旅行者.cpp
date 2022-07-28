/**
 *    unicode: UTF-8
 *    name:    P5304 [GXOI/GZOI2019]旅行者
 *    author:  wangjunrui
 *    created: 2022.07.26 周二 21:20:55 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
#include <queue>
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
constexpr int N = 1e5 + 5, M = 5e5 + 5;
int n, m, k, a[N];
struct Edge
{
    int next, to, dis;
} edge[M];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int b[N], totb;
int c[N], totc;
ll dis[N];
bool vis[N];
ll answer = 1e18;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
inline void dijkstra(int pos)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= k; ++i)
        if ((i >> pos) & 1)
            q.push(make_pair(dis[a[i]] = 0, a[i]));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
                q.push(make_pair(dis[v] = dis[u] + edge[i].dis, v));
        }
    }
    for (int i = 1; i <= k; ++i)
        if (((i >> pos) & 1) ^ 1)
            ckmin(answer, dis[a[i]]);

    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= k; ++i)
        if (((i >> pos) & 1) ^ 1)
            q.push(make_pair(dis[a[i]] = 0, a[i]));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
                q.push(make_pair(dis[v] = dis[u] + edge[i].dis, v));
        }
    }
    for (int i = 1; i <= k; ++i)
        if ((i >> pos) & 1)
            ckmin(answer, dis[a[i]]);
}
inline void work()
{
    read(n, m, k);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
    }
    for (int i = 1; i <= k; ++i)
        read(a[i]);
    int limit = (int)__builtin_log2(k);
    for (int i = 0; i <= limit; ++i)
        dijkstra(i);
    printf("%lld\n", answer);
    answer = 1e18;
    memset(head, num_edge = 0, sizeof(head));
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}