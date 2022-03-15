#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eps 1e-6
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
const int N = 205, M = 1e5 + 5;
struct Edge
{
    int next, to, flow, cap;
    double cost;
} edge[M];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, double cost, bool flag = true)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].flow = 0;
    edge[num_edge].cap = cap;
    edge[num_edge].cost = cost;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, 1 / cost, false);
}
double dis[N];
int cur[N];
bool exist[N];
int S, T;
inline bool spfa()
{
    memset(exist, 0, sizeof(exist));
    memcpy(cur, head, sizeof(head));
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    dis[S] = 1;
    q.push(S);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (edge[i].cap > edge[i].flow && dis[v] < dis[u] * edge[i].cost)
            {
                dis[v] = dis[u] * edge[i].cost;
                if (!exist[v])
                {
                    q.push(v);
                    exist[v] = true;
                }
            }
        }
    }
    return dis[T] > 0;
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
        if (!exist[v] && fabs(dis[v] - dis[u] * edge[i].cost) < eps && edge[i].cap > edge[i].flow)
        {
            int f = dinic(v, min(flow, edge[i].cap - edge[i].flow));
            if (f)
            {
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
                res += f;
                flow -= f;
                if (!f)
                {
                    exist[u] = false;
                    break;
                }
            }
        }
    }
    return res;
}
int n, m;
inline double mcmf()
{
    double ans = 1;
    while (spfa())
    {
        int f = dinic(S, 0x7fffffff);
        // printf("%d\n", f);
        ans *= pow(dis[T], f);
    };
    return ans;
}
int id[105][105];
signed main()
{
    read(n, m);
    S = 0, T = n + m + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int x;
            read(x);
            if (x)
            {
                add_edge(i, j + n, 1, x * 0.01);
                id[i][j] = num_edge - 1;
            }
        }
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        add_edge(S, i, x, 1.0);
    }
    for (int i = 1; i <= m; ++i)
    {
        int x;
        read(x);
        // printf("%d\n", x);
        add_edge(i + n, T, x, 1.0);
    }
    mcmf();
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            putchar('0' + (edge[id[i][j]].flow == 1));
        putchar('\n');
    }
    return 0;
}