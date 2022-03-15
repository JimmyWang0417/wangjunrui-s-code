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
const int N = 2e5 + 5;
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
ll dis[N][4];
bool vis[N][4];
int n, m;
inline void dijkstra(int S)
{
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>, greater<pair<ll, pair<int, int>>>> q;
    q.push(make_pair(dis[S][3] = 0, make_pair(S, 3)));
    while (!q.empty())
    {
        const int u = q.top().second.first, d = q.top().second.second;
        q.pop();
        if (vis[u][d])
            continue;
        vis[u][d] = true;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v][d] > dis[u][d] + edge[i].dis)
                q.push(make_pair(dis[v][d] = dis[u][d] + edge[i].dis, make_pair(v, d)));
            if (d & 1)
            {
                if (dis[v][d ^ 1] > dis[u][d])
                    q.push(make_pair(dis[v][d ^ 1] = dis[u][d], make_pair(v, d ^ 1)));
            }
            if (d & 2)
            {
                if (dis[v][d ^ 2] > dis[u][d] + edge[i].dis * 2)
                    q.push(make_pair(dis[v][d ^ 2] = dis[u][d] + edge[i].dis * 2, make_pair(v, d ^ 2)));
            }
            if ((d & 3) == 3)
            {
                if (dis[v][d ^ 3] > dis[u][d] + edge[i].dis)
                    q.push(make_pair(dis[v][d ^ 3] = dis[u][d] + edge[i].dis, make_pair(v, d ^ 3)));
            }
        }
    }
    for (int i = 2; i <= n; ++i)
        printf("%lld ", dis[i][0]);
    putchar('\n');
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dijkstra(1);
    return 0;
}