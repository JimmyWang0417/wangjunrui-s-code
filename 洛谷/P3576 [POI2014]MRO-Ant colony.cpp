#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 1e6 + 5;
const int MAX = 1e9 + 1;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int deg[N];
int n, m, k, a[N];
int S, T;
ll dp[N];
inline void dfs(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        if (deg[v] == 1)
            dp[v] = dp[u];
        else
            dp[v] = min(dp[u] * (deg[v] - 1), (ll)MAX);
        dfs(v, u);
    }
}
signed main()
{
    read(n, m, k);
    for (int i = 1; i <= m; ++i)
        read(a[i]);
    sort(a + 1, a + 1 + m);
    read(S, T);
    ++deg[S], ++deg[T];
    for (int i = 2; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
        ++deg[u], ++deg[v];
    }
    dp[S] = deg[S] - 1, dp[T] = deg[T] - 1;
    dfs(S, 0);
    dfs(T, 0);
    ll res = 0;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1)
        {
            if (i == S || i == T)
                res += upper_bound(a + 1, a + 1 + m, k) - lower_bound(a + 1, a + 1 + m, k);
            else
                res += upper_bound(a + 1, a + 1 + m, (int)min(dp[i] * (k + 1) - 1, (ll)MAX)) - lower_bound(a + 1, a + 1 + m, (int)min(dp[i] * k, (ll)MAX));
        }
    printf("%lld\n", res * k);
    return 0;
}