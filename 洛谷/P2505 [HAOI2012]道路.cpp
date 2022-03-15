// Problem: P2505 [HAOI2012]道路
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2505
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 1505, M = 5005, mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m;
struct Edge
{
    int next, to, dis;
} edge[M];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int dis[N];
int cnt1[N], cnt2[N];
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>> q;
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>>::point_iterator its[N];
int que[N], tot;
ll answer[M];
inline void dijkstra(int s)
{
    memset(cnt1, 0, sizeof(cnt1));
    memset(cnt2, 0, sizeof(cnt2));
    for (int i = 1; i <= n; ++i)
    {
        if (i != s)
        {
            cnt1[i] = 0;
            its[i] = q.push(make_pair(dis[i] = 0x3f3f3f3f, i));
        }
        else
        {
            cnt1[i] = 1;
            its[i] = q.push(make_pair(dis[i] = 0, i));
        }
    }
    tot = 0;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        que[++tot] = u;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
            {
                cnt1[v] = cnt1[u];
                q.modify(its[v], make_pair(dis[v] = dis[u] + edge[i].dis, v));
            }
            else if (dis[v] == dis[u] + edge[i].dis)
                add(cnt1[v], cnt1[u]);
        }
    }
    for (int now = tot; now >= 1; --now)
    {
        int u = que[now];
        cnt2[u] = 1;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] == dis[u] + edge[i].dis)
                add(cnt2[u], cnt2[v]);
        }
    }
    for (int u = 1; u <= n; ++u)
    {
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] == dis[u] + edge[i].dis)
                (answer[i] += cnt1[u] * cnt2[v]) %= mod;
        }
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
    }
    for (int i = 1; i <= n; ++i)
        dijkstra(i);
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}