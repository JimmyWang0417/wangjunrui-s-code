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
const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m;
struct Edge
{
    int next, to, cap, flow, cost;
} edge[N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, int cost, bool flag = true)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].cap = cap;
    edge[num_edge].flow = 0;
    edge[num_edge].cost = cost;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, -cost, false);
}
int dis[N];
int S, T;
bool exist[N];
int cur[N];
inline bool spfa()
{
    memcpy(cur, head, sizeof(head));
    memset(exist, 0, sizeof(exist));
    memset(dis, INF, sizeof(dis));
    queue<int> q;
    q.push(S);
    dis[S] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].cost && edge[i].cap > edge[i].flow)
            {
                dis[v] = dis[u] + edge[i].cost;
                if (!exist[v])
                    q.push(v);
            }
        }
    }
    return dis[T] < INF / 2;
    ;
}
inline int dinic(int u, int flow)
{
    if (u == T)
        return flow;
    exist[u] = true;
    int res = 0;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (!exist[v] && dis[v] == dis[u] + edge[i].cost && edge[i].cap > edge[i].flow)
        {
            int f = dinic(v, min(flow, edge[i].cap - edge[i].flow));
            if (f)
            {
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
                res += f;
                flow -= f;
                if (!flow)
                {
                    exist[u] = false;
                    break;
                }
            }
        }
    }
    return res;
}
inline void mcmf()
{
    int res = 0, ans = 0;
    while (spfa())
    {
        int f = dinic(S, INF);
        res += f;
        ans += f * dis[T];
    }
    printf("%d %d\n", res, ans);
}
signed main()
{
    read(n, m);
    S = 1 + n, T = n;
    for (int i = 2; i < n; ++i)
        add_edge(i, i + n, 1, 0);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u + n, v, 1, w);
    }
    mcmf();
    return 0;
}