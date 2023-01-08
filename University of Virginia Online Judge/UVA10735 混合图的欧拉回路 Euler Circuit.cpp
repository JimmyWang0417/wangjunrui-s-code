#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 1e3 + 5;
int n, m;
struct Edge
{
    int next, to, flow, cap;
} edge[N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, bool flag = true)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].cap = cap;
    edge[num_edge].flow = 0;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, false);
}
int cur[N], dis[N];
int S, T;
inline bool bfs()
{
    memset(dis, 0, sizeof(dis));
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
    int res = 0;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (dis[v] == dis[u] + 1 && edge[i].cap > edge[i].flow)
        {
            int f = dinic(v, min(edge[i].cap - edge[i].flow, flow));
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
struct node
{
    int u, v;
} e[N];
int id[N];
int deg[N];
list<int> g[N];
inline int maxflow()
{
    int res = 0;
    while (bfs())
        res += dinic(S, INT_MAX);
    return res;
}
int st[N], top;
inline void dfs(int u)
{
    while (!g[u].empty())
    {
        int v = g[u].front();
        g[u].pop_front();
        dfs(v);
    }
    st[++top] = u;
}
inline void work()
{
    memset(deg, 0, sizeof(deg));
    memset(head, 0, sizeof(head));
    num_edge = 1;
    read(n, m);
    S = 0, T = n + 1;
    for (int i = 1; i <= m; ++i)
    {
        int &u = e[i].u, &v = e[i].v;
        char opt[10];
        read(u, v), scanf("%s", opt);
        --deg[u], ++deg[v];
        if (opt[0] == 'D')
            id[i] = -1;
        else
        {
            add_edge(v, u, 2);
            id[i] = num_edge - 1;
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (deg[i] & 1)
        {
            printf("No euler circuit exist\n");
            return;
        }
        if (deg[i] > 0)
        {
            add_edge(S, i, deg[i]);
            sum += deg[i];
        }
        else if (deg[i] < 0)
            add_edge(i, T, -deg[i]);
    }
    if (maxflow() != sum)
    {
        printf("No euler circuit exist\n");
        return;
    }
    for (int i = 1; i <= m; ++i)
        if (id[i] >= 0 && edge[id[i]].flow == edge[id[i]].cap)
            g[e[i].v].push_back(e[i].u);
        else
            g[e[i].u].push_back(e[i].v);
    dfs(1);
    while (top)
        printf("%d ", st[top--]);
    putchar('\n');
}
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        work();
        if (T)
            putchar('\n');
    }
    return 0;
}