#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
template <typename T>
inline void read(T &x)
{
    x = 0;
    static char s = (char)getchar();
    static bool f = false;
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
const int N = 3e5 + 5;
int n;
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
int a[N];
int dp[N];
int size[N];
inline void dfs(int u)
{
    if (a[u])
    {
        dp[u] = n;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            dfs(v);
            ckmin(dp[u], dp[v]);
            size[u] += size[v];
        }
    }
    else
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            dfs(v);
            dp[u] += dp[v];
            size[u] += size[v];
        }
    if (!size[u])
        size[u] = dp[u] = 1;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa);
        add_edge(_fa, i);
    }
    dfs(1);
    printf("%d\n", size[1] - dp[1] + 1);
    return 0;
}