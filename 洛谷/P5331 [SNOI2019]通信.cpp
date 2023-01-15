/**
 *    unicode: UTF-8
 *    name:    P5331 [SNOI2019]通信
 *    author:  whitepaperdog
 *    created: 2022.08.06 周六 12:39:49 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <numeric>
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
constexpr int N = 1e6 + 5;
int n, m;
struct Edge
{
    int next, to, cap, flow, cost;
} edge[N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, int cost, bool flag = true)
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
int S, T;
ll dis[N];
int cur[N];
bool exist[N];
struct Queue
{
    int q[N];
    int head, tail;
    inline void clear()
    {
        head = 1;
        tail = 0;
    }
    inline bool empty()
    {
        return head > tail;
    }
    inline void push(int x)
    {
        q[++tail] = x;
    }
    inline int front()
    {
        return q[head];
    }
    inline void pop()
    {
        ++head;
    }
} q;
inline bool spfa()
{
    fill(dis + S, dis + T + 1, 1e18);
    copy(head + S, head + T + 1, cur + S);
    fill(exist + S, exist + T + 1, 0);
    q.clear();
    q.push(S);
    dis[S] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].cost && edge[i].cap > edge[i].flow)
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
    return dis[T] < (ll)1e18;
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
        if (!exist[v] &&
            dis[v] == dis[u] + edge[i].cost && edge[i].cap > edge[i].flow)
        {
            int f = dinic(v, min(edge[i].cap - edge[i].flow, flow));
            if (f)
            {
                res += f;
                flow -= f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
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
int a[N], b[N];
int tot;
inline void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    int cnt = r - l + 1;
    iota(b + 1, b + cnt + 1, l);
    sort(b + 1, b + cnt + 1, [](int x, int y)
         { return a[x] < a[y]; });
    for (int i = 1; i < cnt; ++i)
    {
        add_edge(tot + i, tot + i + 1, 0x7fffffff, a[b[i + 1]] - a[b[i]]);
        add_edge(tot + i + 1, tot + i, 0x7fffffff, a[b[i + 1]] - a[b[i]]);
    }
    for (int i = 1; i <= cnt; ++i)
    {
        if (b[i] <= mid)
            add_edge(tot + i, b[i] + n, 1, 0);
        else
            add_edge(b[i], tot + i, 1, 0);
    }
    tot += cnt;
    solve(l, mid);
    solve(mid + 1, r);
}
inline ll mincost_maxflow()
{
    ll res = 0;
    while (spfa())
        res += dinic(S, 0x7fffffff) * dis[T];
    return res;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    tot = 2 * n;
    solve(1, n);
    S = 0, T = tot + 1;
    for (int i = 1; i <= n; ++i)
    {
        add_edge(S, i, 1, 0);
        add_edge(i, T, 1, m);
        add_edge(i + n, T, 1, 0);
    }
    printf("%lld\n", mincost_maxflow());
    return 0;
}