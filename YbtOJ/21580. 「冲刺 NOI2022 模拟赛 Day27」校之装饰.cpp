#include <bitset>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
#define lll __int128
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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 205;
int n, m, k, a[N];
int S, T;
int id[N][N];
namespace MAXFLOW
{
    struct Edge
    {
        int next, to, flow, cap;
    } edge[N * N];
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
    bool exist[N];
    int dis[N], cur[N];
    inline bool bfs()
    {
        memset(dis, 0, sizeof(dis));
        memset(exist, 0, sizeof(exist));
        memcpy(cur, head, sizeof(head));
        queue<int> q;
        q.push(S);
        dis[S] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == T)
                return true;
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
        return false;
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
            if (!exist[v] && dis[v] == dis[u] + 1 && edge[i].cap > edge[i].flow)
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
    inline int maxflow()
    {
        int res = 0;
        while (bfs())
            res += dinic(S, INT_MAX);
        return res;
    }
}
namespace SOLVE
{
    struct Edge
    {
        int next, to, id;
    } edge[N * N];
    int deg[N];
    bool del[N * N];
    int head[N], num_edge = 1;
    inline void add_edge(int from, int to, int id, bool flag = true)
    {
        edge[++num_edge].next = head[from];
        edge[num_edge].to = to;
        edge[num_edge].id = id;
        head[from] = num_edge;
        ++deg[to];
        if (flag)
            add_edge(to, from, id, false);
    }
    int minn;
    int belong[N], lasedge[N];
    bitset<N> vis;
    bitset<N> ok;
    inline bool find(int u)
    {
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (del[i] || vis[v] || !ok[v])
                continue;
            vis[v] = true;
            if (!belong[v] || find(belong[v]))
            {
                belong[u] = v;
                belong[v] = u;
                lasedge[u] = lasedge[v] = i;
                return true;
            }
        }
        return false;
    }
    inline void solve(int color)
    {
        ok.set();
        for (int i = 1; i <= n; ++i)
            if (deg[i] == color && !belong[i])
            {
                ok[i] = find(i);
                vis.reset();
            }
        for (int i = 1; i <= n; ++i)
            if (deg[i] < color && !belong[i])
            {
                ok[i] = find(i);
                vis.reset();
            }
        memset(belong, 0, sizeof(belong));
        for (int i = n / 2 + 1; i <= n; ++i)
            if (deg[i] == color)
            {
                ok[i] = find(i);
                vis.reset();
            }
        for (int i = n / 2 + 1; i <= n; ++i)
            if (deg[i] < color)
            {
                ok[i] = find(i);
                vis.reset();
            }
        for (int i = 1; i <= n / 2; ++i)
            if (belong[i])
            {
                del[lasedge[i]] = del[lasedge[i] ^ 1] = true;
                printf("%d %d\n", edge[lasedge[i]].id, color);
                --deg[i], --deg[belong[i]];
            }
        memset(belong, 0, sizeof(belong));
    }
    inline void print()
    {
        for (int i = 2; i <= num_edge; i += 2)
            if (!del[i])
                printf("%d\n", edge[i].id);
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("decorate.in", "r", stdin);
    freopen("decorate.out", "w", stdout);
#endif
    read(n, m, k);
    S = 0, T = n + 1;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        MAXFLOW::add_edge(x, y, 1);
        id[x][y] = MAXFLOW::num_edge - 1;
    }
    for (int i = 1; i <= n / 2; ++i)
    {
        MAXFLOW::add_edge(S, i, k);
        id[i][0] = MAXFLOW::num_edge - 1;
    }
    for (int i = n / 2 + 1; i <= n; ++i)
    {
        MAXFLOW::add_edge(i, T, k);
        id[i][0] = MAXFLOW::num_edge - 1;
    }
    printf("%d\n", MAXFLOW::maxflow());
    for (int i = 1; i <= n; ++i)
        a[i] = MAXFLOW::edge[id[i][0]].flow;
    for (int i = 1; i <= n / 2; ++i)
        for (int j = n / 2 + 1; j <= n; ++j)
        {
            if (MAXFLOW::edge[id[i][j]].flow == 1)
                SOLVE::add_edge(i, j, id[i][j] / 2);
        }
    for (int i = k; i >= 1; --i)
        SOLVE::solve(i);
    SOLVE::print();
    return 0;
}
