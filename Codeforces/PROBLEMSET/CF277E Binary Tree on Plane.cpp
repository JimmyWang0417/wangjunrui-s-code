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
const int N = 1e5 + 5, M = 1e6 + 5;
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
    edge[num_edge].cap = cap;
    edge[num_edge].flow = 0;
    edge[num_edge].cost = cost;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, -cost, false);
}
int cur[N];
double dis[N];
bool exist[N];
int S, T;
inline bool spfa()
{
    memcpy(cur, head, sizeof(cur));
    memset(exist, 0, sizeof(exist));
    for (int i = S; i <= T; ++i)
        dis[i] = 1e9;
    queue<int> q;
    q.push(S);
    dis[S] = 0;
    exist[S] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost)
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
    return dis[T] < 1e6;
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
            int f = dinic(v, std::min(flow, edge[i].cap - edge[i].flow));
            if (f)
            {
                res += f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
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
inline pair<int, double> maxflowmincost()
{
    double res = 0;
    int flow = 0;
    while (spfa())
    {
        int add = dinic(S, 0x7fffffff);
        flow += add;
        res += add * dis[T];
    }
    return make_pair(flow, res);
}
int n;
struct Point
{
    int x, y;
} a[N];
inline double calc(int x, int y)
{
    return (sqrt((double)(a[x].x - a[y].x) * (a[x].x - a[y].x) + (double)(a[x].y - a[y].y) * (a[x].y - a[y].y)));
}
signed main()
{
    read(n);
    S = 0, T = 2 * n + 1;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].x, a[i].y);
        add_edge(S, i, 2, 0);
        add_edge(i + n, T, 1, 0);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (a[i].y > a[j].y)
                add_edge(i, j + n, 1, calc(i, j));
    pair<int, double> now = maxflowmincost();
    if (now.first == n - 1)
        printf("%lf\n", now.second);
    else
        printf("-1\n");
    return 0;
}
