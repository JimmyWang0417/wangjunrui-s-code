#include <bits/stdc++.h>
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
vector<int> g[N];
int dp[N];
inline void dfs(int u)
{
    for (auto v : g[u])
        dfs(v);
    sort(g[u].begin(), g[u].end(), [](int x, int y)
         { return dp[x] < dp[y]; });
    for (auto v : g[u])
        dp[u] = max(dp[u], dp[v]) + 1;
}
signed main()
{
    read(n);
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa);
        g[_fa].push_back(i);
    }
    dfs(1);
    printf("%d\n", dp[1]);
    return 0;
}