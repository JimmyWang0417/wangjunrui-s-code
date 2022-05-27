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
const int N = 5e4 + 5, M = 1e5 + 5;
int n, m;
struct node
{
    int u, v, w1, w2;
} e[N];
struct Edge
{
    int next, to, cap, flow;
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
int dis[N], cur[N];
int S, T;
inline bool bfs()
{
    memcpy(cur, head, sizeof(cur));
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    q.push(S);
    dis[S] = 1;
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
inline int maxflow()
{
    int res = 0;
    while (bfs())
        res += dinic(S, INT_MAX);
    return res;
}
int deg[N];
inline bool check(int val)
{
    num_edge = 1;
    memset(head, 0, sizeof(head));
    memset(deg, 0, sizeof(deg));
    for (int i = 1; i <= m; ++i)
    {
        if (e[i].w1 <= val)
        {
            ++deg[e[i].u];
            --deg[e[i].v];
            if (e[i].w2 <= val)
                add_edge(e[i].u, e[i].v, 1);
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (deg[i] & 1)
            return false;
        deg[i] /= 2;
        if (deg[i] > 0)
        {
            add_edge(S, i, deg[i]);
            sum += deg[i];
        }
        else if (deg[i] < 0)
            add_edge(i, T, -deg[i]);
    }
    return sum == maxflow();
}
int id[N];
list<pair<int, int>> g[N];
inline void print(int u)
{
    while (!g[u].empty())
    {
        int v = g[u].back().first, w = g[u].back().second;
        g[u].pop_back();
        print(v);
        printf("%d ", w);
    }
}
inline void solve(int val)
{
    num_edge = 1;
    memset(head, 0, sizeof(head));
    memset(deg, 0, sizeof(deg));
    for (int i = 1; i <= m; ++i)
    {
        if (e[i].w1 <= val)
        {
            ++deg[e[i].u];
            --deg[e[i].v];
            if (e[i].w2 <= val)
            {
                add_edge(e[i].u, e[i].v, 1);
                id[i] = num_edge - 1;
            }
            else
                id[i] = -1;
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        deg[i] /= 2;
        if (deg[i] > 0)
        {
            add_edge(S, i, deg[i]);
            sum += deg[i];
        }
        else if (deg[i] < 0)
            add_edge(i, T, -deg[i]);
    }
    maxflow();
    for (int i = 1; i <= m; ++i)
        if (id[i] >= 0 && edge[id[i]].flow == edge[id[i]].cap)
            g[e[i].u].push_back(make_pair(e[i].v, i));
        else
            g[e[i].v].push_back(make_pair(e[i].u, i));
    print(1);
    putchar('\n');
}
signed main()
{
    read(n, m);
    S = 0, T = n + 1;
    int minn = 0, maxx = 0;
    for (int i = 1; i <= m; ++i)
    {
        read(e[i].u, e[i].v, e[i].w1, e[i].w2);
        if (e[i].w1 > e[i].w2)
        {
            swap(e[i].u, e[i].v);
            swap(e[i].w1, e[i].w2);
        }
        ++deg[e[i].u];
        ++deg[e[i].v];
        ckmax(minn, min(e[i].w1, e[i].w2));
        ckmax(maxx, max(e[i].w1, e[i].w2));
    }
    for (int i = 1; i <= n; ++i)
        if (deg[i] & 1)
        {
            printf("NIE\n");
            return 0;
        }
    memset(deg, 0, sizeof(deg));
    int l = minn, r = maxx, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    printf("%d\n", ans);
    solve(ans);
    return 0;
}