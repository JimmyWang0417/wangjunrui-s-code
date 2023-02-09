// Problem: C. Heidi and Library (hard)
// Contest: Codeforces - Helvetic Coding Contest 2017 online mirror (teams allowed, unrated)
// URL: https://codeforces.com/problemset/problem/802/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
constexpr int N = 2005;
int n, k;
struct Edge
{
    int next, to, flow, cap, cost;
} edge[N * 10];
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
bool exist[N];
int dis[N], cur[N];
int S, T;
inline bool spfa()
{
    memset(exist, false, sizeof(exist));
    memset(dis, 0x3f, sizeof(dis));
    memcpy(cur, head, sizeof(cur));
    dis[S] = 0;
    queue<int> q;
    q.push(S);
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
    return dis[T] < 0x3f3f3f3f;
}
inline int dinic(int u, int flow)
{
    if (u == T)
        return flow;
    int res = 0;
    exist[u] = true;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (!exist[v] && edge[i].cap > edge[i].flow && dis[v] == dis[u] + edge[i].cost)
        {
            int f = dinic(v, min(flow, edge[i].cap - edge[i].flow));
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
int mp[N];
int a[N], b[N];
signed main()
{
    read(n, k);
    S = 0, T = 2 * n + 1;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        add_edge(i, i + n, 1, 0);
        add_edge(i + n, T, 1, 0);
    }
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        add_edge(S, i, 1, b[a[i]]);
        if (mp[a[i]])
            add_edge(i - 1, mp[a[i]] + n, 1, -b[a[i]]);
        mp[a[i]] = i;
    }
    for (int i = 1; i < n; ++i)
        add_edge(i, i + 1, k - 1, 0);
    while (spfa())
        ans += dis[T] * dinic(S, INT_MAX);
    printf("%d\n", ans);
    return 0;
}