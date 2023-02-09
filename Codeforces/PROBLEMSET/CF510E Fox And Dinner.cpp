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
const int N = 1e5 + 5;
const int INF = 0x7fffffff;
bitset<N> vis;
int prime[N], tot;
inline void getprime(int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot; ++j)
        {
            if (prime[j] * i > n)
                break;
            vis.set(prime[j] * i);
            if (i % prime[j] == 0)
                break;
        }
    }
}
struct Edge
{
    int next, to, flow, cap;
} edge[N];
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
int dis[N], cur[N];
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
    //	for(int i=S; i<=T; ++i)
    //		printf("%d ",dis[i]);
    //	putchar('\n');
    return dis[T];
}
inline int dinic(int u, int flow)
{
    if (u == T)
        return flow;
    int res = 0;
    for (int i = cur[u]; i; i = edge[i].next)
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
        res += dinic(S, INF);
    return res;
}
int n, a[N];
vector<int> answer[N];
int anstot;
inline void dfs(int u)
{
    vis.set(u);
    answer[anstot].push_back(u);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (edge[i & (~1)].cap == edge[i & (~1)].flow)
        {
            if (vis[v])
                continue;
            dfs(v);
        }
    }
}
signed main()
{
    getprime(20000);
    read(n);
    S = 0, T = n + 1;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        if (a[i] & 1)
        {
            add_edge(S, i, 2);
            for (int j = 1; j <= n; ++j)
                if (!vis[a[i] + a[j]])
                    add_edge(i, j, 1);
        }
        else
            add_edge(i, T, 2);
    if (maxflow() != n)
    {
        printf("Impossible\n");
        return 0;
    }
    vis.reset();
    vis.set(S), vis.set(T);
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
        {
            dfs(i);
            ++anstot;
        }
    printf("%d\n", anstot);
    for (int now = 0; now < anstot; ++now)
    {
        printf("%d", (int)answer[now].size());
        for (int i : answer[now])
            printf(" %d", i);
        putchar('\n');
    }
    return 0;
}
