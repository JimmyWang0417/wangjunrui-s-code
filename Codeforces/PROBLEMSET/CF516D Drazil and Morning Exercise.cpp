#include <cstdio>
#include <vector>
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
constexpr int N = 1e5 + 5;
int n, q;
struct Edge
{
    int next, to, dis;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
ll dis[N], dis1[N], dis2[N];
int S = 1, T = 1;
inline void dfs1(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dis1[v] = dis1[u] + edge[i].dis;
        dfs1(v, u);
    }
}
inline void dfs2(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dis2[v] = dis2[u] + edge[i].dis;
        dfs2(v, u);
    }
}
int answer, dp[N];
vector<ll> f;
vector<int> g;
inline void dfs(int u, int _fa, ll len)
{
    f.push_back(dis[u]);
    g.push_back(u);
    dp[u] = 1;
    --dp[g[lower_bound(f.begin(), f.end(), dis[u] - len) - f.begin() - 1]];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u, len);
        dp[u] += dp[v];
    }
    ckmax(answer, dp[u]);
    f.pop_back();
    g.pop_back();
}
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i)
        if (dis1[S] < dis1[i])
            S = i;
    dis1[S] = 0;
    dfs1(S, 0);
    for (int i = 1; i <= n; ++i)
        if (dis1[T] < dis1[i])
            T = i;
    dfs2(T, 0);
    int root = 1;
    for (int i = 1; i <= n; ++i)
    {
        dis[i] = max(dis1[i], dis2[i]);
        if (dis[i] < dis[root])
            root = i;
    }
    f.push_back(-1e18);
    g.push_back(0);
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        ll x;
        read(x);
        dfs(root, 0, x);
        printf("%d\n", answer);
        answer = 0;
    }
    return 0;
}