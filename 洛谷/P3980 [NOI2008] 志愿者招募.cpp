#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e4 + 5, M = 2e5 + 5;
const int INF = 0x7fffffff;
int n, m;
struct Edge
{
    int next, to, flow, cap, cost;
} edge[M];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, int cost, bool flag = true)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].flow = 0;
    edge[num_edge].cap = cap;
    edge[num_edge].cost = cost;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, -cost, false);
}
int S, T;
int dis[N], cur[N];
bool exist[N];
inline bool spfa()
{
    memset(dis, 0x3f, sizeof(int) * (n + 2));
    memcpy(cur, head, sizeof(int) * (n + 2));
    memset(exist, 0, sizeof(bool) * (n + 2));
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
                {
                    exist[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return dis[T] < INF / 4;
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
                res += f;
                flow -= f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
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
inline ll mincost_maxflow()
{
    ll res = 0;
    while (spfa())
        res += (ll)dis[T] * dinic(S, INF);
    return res;
}
signed main()
{
    read(n, m);
    S = 0, T = n + 1;
    add_edge(S, 1, INF, 0);
    for (int i = 1; i <= n; ++i)
    {
        int val;
        read(val);
        add_edge(i, i + 1, INF - val, 0);
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v, c;
        read(u, v, c);
        add_edge(u, v + 1, INF, c);
    }
    printf("%lld\n", mincost_maxflow());
    return 0;
}
