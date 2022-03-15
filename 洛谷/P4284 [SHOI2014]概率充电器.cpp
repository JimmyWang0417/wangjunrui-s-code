#include <bits/stdc++.h>
#define eps 1e-18
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
const int N = 5e5 + 5;
int n;
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
double dp[N];
inline void dfs(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        double w = dp[v] * edge[i].dis * 0.01;
        dp[u] = dp[u] + w - dp[u] * w;
    }
}
double answer;
inline void solve(int u, int _fa, double p)
{
    dp[u] = dp[u] + p - dp[u] * p;
    answer += dp[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        if (fabs(dp[v] - 1) < eps)
        {
            solve(v, u, 0);
            continue;
        }
        double w = 0.01 * edge[i].dis;
        solve(v, u, w * (dp[u] - dp[v] * w) / (1 - dp[v] * w));
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
        int x;
        read(x);
        dp[i] = x * 0.01;
    }
    dfs(1, 0);
    solve(1, 0, 0);
    printf("%lf\n", answer);
    return 0;
}