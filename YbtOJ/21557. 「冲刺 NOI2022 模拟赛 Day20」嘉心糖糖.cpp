#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
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
constexpr int N = 2010;
constexpr int INF = 0x3f3f3f3f;
int n;
struct Edge
{
    int next, to, flow, cap, cost;
} edge[N * 100];
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
int cur[N];
ll dis[N];
bool exist[N];
inline bool spfa()
{
    memset(exist, 0, sizeof(exist));
    memset(dis, ~0x3f, sizeof(dis));
    memcpy(cur, head, sizeof(head));
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
            if (edge[i].cap > edge[i].flow && dis[v] < dis[u] + edge[i].cost)
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
    return dis[T] > -1000000000000000000ll;
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
        if (!exist[v] && edge[i].cap > edge[i].flow && dis[v] == dis[u] + edge[i].cost)
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
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("Diana.in","r",stdin);
    freopen("Diana.out","w",stdout);
#endif
    read(n);
    S = 0, T = 2 * n + 5;
    for (int i = 1; i <= n; ++i)
    {
        int x, y, c;
        read(x, y, c);
        add_edge(S, i, c, 0);
        add_edge(i, 2 * n + 1, c, +x + y);
        add_edge(i, 2 * n + 2, c, +x - y);
        add_edge(i, 2 * n + 3, c, -x + y);
        add_edge(i, 2 * n + 4, c, -x - y);
    }
    for (int i = 1; i <= n; ++i)
    {
        int x, y, c;
        read(x, y, c);
        add_edge(i + n, T, c, 0);
        add_edge(2 * n + 1, i + n, c, -x - y);
        add_edge(2 * n + 2, i + n, c, -x + y);
        add_edge(2 * n + 3, i + n, c, +x - y);
        add_edge(2 * n + 4, i + n, c, +x + y);
    }
    ll res = 0;
    while (spfa())
        res += dinic(S, INF) * dis[T];
    printf("%lld\n", res);
    return 0;
}
