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
const int N = 1505;
struct Edge
{
    int next, to, dis;
    bool flag;
} edge[N * N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int n, m;
int s1, t1, s2, t2;
int dis1[N], dis2[N], dis3[N], dis4[N];
bool vis[N];
int Q[N * N], tot;
inline void dijkstra1(int *dis, int s, int t)
{
    memset(vis, 0, sizeof(vis));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(dis[s] = 0, s));
    tot = 0;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        Q[++tot] = u;
        if (u == t)
            break;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
                q.push(make_pair(dis[v] = dis[u] + edge[i].dis, v));
        }
    }
}
inline void dijkstra2(int *dis, int s, int t)
{
    memset(vis, 0, sizeof(vis));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(dis[s] = 0, s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (u == t)
            break;
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
}
inline void solve1()
{
    for (int i = 1; i <= tot; ++i)
    {
        int u = Q[i];
        for (int e = head[u]; e; e = edge[e].next)
        {
            int &v = edge[e].to;
            // printf("%d %d %d %d\n",u,v,dis1[u] + edge[e].dis + dis2[v],dis1[t1]);
            if (dis1[u] + edge[e].dis + dis2[v] == dis1[t1])
                edge[e].flag = edge[e ^ 1].flag = true;
        }
    }
}
int answer[N];
inline int solve2()
{
    for (int i = 1; i <= tot; ++i)
    {
        int u = Q[i];
        for (int e = head[u]; e; e = edge[e].next)
        {
            int &v = edge[e].to;
            if (dis3[u] + edge[e].dis + dis4[v] == dis3[t2] && answer[v] < answer[u] + edge[e].dis + edge[e].flag)
                answer[v] = answer[u] + edge[e].dis * edge[e].flag;
        }
    }
    return answer[t2];
}
signed main()
{
    read(n, m);
    read(s1, t1, s2, t2);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    memset(dis1, 0x3f, sizeof(dis1));
    memset(dis2, 0x3f, sizeof(dis2));
    memset(dis3, 0x3f, sizeof(dis3));
    memset(dis4, 0x3f, sizeof(dis4));
    dijkstra1(dis1, s1, t1);
    dijkstra2(dis2, t1, s1);
    solve1();
    dijkstra1(dis3, s2, t2);
    dijkstra2(dis4, t2, s2);
    printf("%d\n", solve2());
    return 0;
}