#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int INF = 0x7fffffff;
struct Edge
{
    int next, to, flow, cap;
} edge[N * 10];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, bool flag = true)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].flow = 0;
    edge[num_edge].cap = cap;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, false);
}
int S, T;
bool vis[N];
int dis[N], cur[N];
inline bool bfs()
{
    memset(dis, 0, sizeof(dis));
    memcpy(cur, head, sizeof(head));
    queue<int> q;
    dis[S] = 1;
    q.push(S);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (!dis[v] && edge[i].cap > edge[i].flow)
            {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[T];
}
inline int dinic(int u, int flow)
{
    if (u == T)
        return flow;
    int res = 0;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (dis[v] == dis[u] + 1 && edge[i].cap > edge[i].flow)
        {
            int f = dinic(v, std::min(flow, edge[i].cap - edge[i].flow));
            if (f)
            {
                res += f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
                flow -= f;
                if (!flow)
                    break;
            }
        }
    }
    return res;
}
inline int maxflow()
{
    int res = 0;
    while (bfs())
        res += dinic(S, INF);
    return res;
}
int n, m;
inline int calc(int i, int j)
{
    return (i - 1) * m + j;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    int sum = 0;
    S = 0, T = n * m * 6 + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int val;
            cin >> val;
            sum += val;
            add_edge(calc(i, j), T, val);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int val;
            cin >> val;
            sum += val;
            add_edge(S, calc(i, j), val);
        }
    int cnt = n * m;
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int val;
            cin >> val;
            sum += val;
            ++cnt;
            add_edge(calc(i, j), cnt, INF);
            add_edge(calc(i + 1, j), cnt, INF);
            add_edge(cnt, T, val);
        }
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int val;
            cin >> val;
            sum += val;
            ++cnt;
            add_edge(S, cnt, val);
            add_edge(cnt, calc(i, j), INF);
            add_edge(cnt, calc(i + 1, j), INF);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < m; ++j)
        {
            int val;
            cin >> val;
            sum += val;
            ++cnt;
            add_edge(calc(i, j), cnt, INF);
            add_edge(calc(i, j + 1), cnt, INF);
            add_edge(cnt, T, val);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < m; ++j)
        {
            int val;
            cin >> val;
            sum += val;
            ++cnt;
            add_edge(S, cnt, val);
            add_edge(cnt, calc(i, j), INF);
            add_edge(cnt, calc(i, j + 1), INF);
        }
    printf("%d\n", sum - maxflow());
}
