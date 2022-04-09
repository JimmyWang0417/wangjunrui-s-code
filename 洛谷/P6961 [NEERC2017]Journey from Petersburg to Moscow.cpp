#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>
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
constexpr int N = 3005;
int n, m, k;
int p[N], tot;
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
__gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>> q;
__gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>>::point_iterator its[N];
ll dis[N];
inline void dijkstra(int x)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    for (int i = 1; i <= n; ++i)
        its[i] = q.push(make_pair(dis[i], i));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to, w = max(0, edge[i].dis - x);
            if (dis[v] > dis[u] + w)
                q.modify(its[v], make_pair(dis[v] = dis[u] + w, v));
        }
    }
}
signed main()
{
    read(n, m, k);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        p[++tot] = w;
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    ll answer = 1e18;
    for (int i = 0; i <= tot; ++i)
    {
        dijkstra(p[i]);
        ckmin(answer, dis[n] + (ll)p[i] * k);
    }
    printf("%lld\n", answer);
    return 0;
}