#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
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
template <typename T>
inline void clear(T *a, int l, int r, int val)
{
    memset(&a[l], val, sizeof(T) * (r - l + 1));
}
const int N = 105, M = 1005;
struct Edge
{
    int next, to, cap, flow;
} edge[N + N * M];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].cap = cap;
    edge[num_edge].flow = 0;
    head[from] = num_edge;
}
int a[M];
int dis[N], cur[N];
int m, n, s, t;
inline bool bfs()
{
    memset(dis, 0, sizeof(dis));
    for (re int i = 0; i <= n + 1; ++i)
        cur[i] = head[i];
    std::queue<int> q;
    q.push(s);
    dis[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        if (u == t)
            return true;
        q.pop();
        for (re int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (!dis[v] && edge[i].cap > edge[i].flow)
            {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return false;
}
inline int dinic(int u, int flow)
{
    if (u == t || !flow)
        return flow;
    int res = 0;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to, f;
        if (dis[v] == dis[u] + 1 && (f = dinic(v, std::min(flow, edge[i].cap - edge[i].flow))) > 0)
        {
            res += f;
            edge[i].flow += f;
            edge[i ^ 1].flow -= f;
            flow -= f;
            if (!flow)
                return res;
        }
    }
    return res;
}
int las[M];
signed main()
{
    read(m), read(n);
    s = 0, t = n + 1;
    for (re int i = 1; i <= m; ++i)
        read(a[i]);
    for (re int u = 1; u <= n; ++u)
    {
        int cnt, v;
        read(cnt);
        for (re int i = 1; i <= cnt; ++i)
        {
            read(v);
            if (!las[v])
            {
                add_edge(0, u, a[v]);
                add_edge(u, 0, 0);
            }
            else
            {
                add_edge(las[v], u, 0x3f3f3f3f);
                add_edge(u, las[v], 0);
            }
            las[v] = u;
        }
        read(v);
        add_edge(u, n + 1, v);
        add_edge(n + 1, u, 0);
    }
    int ans = 0;
    while (bfs())
        ans += dinic(0, 0x7fffffff);
    printf("%d\n", ans);
    return 0;
}