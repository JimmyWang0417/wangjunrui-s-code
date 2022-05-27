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
const int N = 105 * 105 + 5, M = 1e6 + 5;
const int INF = 0x3f3f3f3f;
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
    memset(dis, INF, sizeof(dis));
    memcpy(cur, head, sizeof(head));
    memset(exist, 0, sizeof(exist));
    queue<int> q;
    dis[S] = 0;
    q.push(S);
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
                    q.push(v);
                    exist[v] = true;
                }
            }
        }
    }
    return dis[T] < INF / 2;
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
                    break;
            }
        }
    }
    return res;
}
inline int mincost_maxflow()
{
    int res = 0;
    while (spfa())
        res += dis[T] * dinic(S, INF);
    return res;
}
int n, m, deg[N], a[N][N];
int id[N][N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            read(a[i][j]);
            deg[i] += (a[i][j] == 1);
        }
    S = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
        {
            if (a[i][j] < 2)
                continue;
            ++m;
            add_edge(S, n + m, 1, 0);
            add_edge(n + m, i, 1, 0);
            id[i][j] = num_edge - 1;
            add_edge(n + m, j, 1, 0);
            id[j][i] = num_edge - 1;
        }
    T = n + m + 1;
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += deg[i] * (deg[i] - 1) / 2;
        for (int j = deg[i]; j < n - 1; ++j)
            add_edge(i, T, 1, j);
    }
    printf("%d\n", n * (n - 1) * (n - 2) / 6 - ans - mincost_maxflow());
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (a[i][j] < 2)
                printf("%d ", a[i][j]);
            else
            {
                if (edge[id[i][j]].flow == edge[id[i][j]].cap)
                    printf("1 ");
                else
                    printf("0 ");
            }
        }
        putchar('\n');
    }
    return 0;
}
