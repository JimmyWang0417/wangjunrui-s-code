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
constexpr int N = 2.5e5 + 5;
constexpr ll INF = 1e12;
int n, a[N];
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
int tot = 0;
ll answer;
__gnu_pbds::priority_queue<ll, greater<ll>> q1[N], q2[N];
inline void dfs(int u, int _fa, ll dis)
{
    if (a[u] > 0)
        while (a[u]--)
            q1[u].push(dis);
    else if (a[u] < 0)
    {
        a[u] = -a[u];
        tot += a[u];
        while (a[u]--)
            q2[u].push(dis - INF);
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u, dis + edge[i].dis);
        q1[u].join(q1[v]), q2[u].join(q2[v]);
    }
    while (!q1[u].empty() && !q2[u].empty() && q1[u].top() + q2[u].top() - dis * 2 < 0)
    {
        ll x = q1[u].top(), y = q2[u].top();
        q1[u].pop(), q2[u].pop();
        answer += x + y - 2 * dis;
        q1[u].push(2 * dis - y);
        q2[u].push(2 * dis - x);
    }
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
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        read(x, y);
        a[i] = x - y;
    }
    dfs(1, 0, 0);
    printf("%lld\n", answer + INF * tot);
    return 0;
}