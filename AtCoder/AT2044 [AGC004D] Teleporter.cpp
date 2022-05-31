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
int n, m;
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
int answer;
int dp[N];
inline void dfs(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
        ckmax(dp[u], dp[v] + 1);
    }
    if (dp[u] >= m)
    {
        dp[u] = -1;
        ++answer;
    }
}
signed main()
{
    read(n, m);
    int _fa;
    read(_fa);
    if (_fa != 1)
        ++answer;
    for (int i = 2; i <= n; ++i)
    {
        read(_fa);
        add_edge(_fa, i);
    }
    --m;
    for (int i = head[1]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        for (int e = head[v]; e; e = edge[e].next)
        {
            int &w = edge[e].to;
            dfs(w);
        }
    }
    printf("%d\n", answer);
    return 0;
}