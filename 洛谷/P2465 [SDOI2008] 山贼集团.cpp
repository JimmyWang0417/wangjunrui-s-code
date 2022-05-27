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
using namespace std;
const int N = 105, M = (1 << 12) + 5;
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
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
int n, p, t;
int a[N][N];
ll dp[N][M], g[M];
inline void dfs(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        for (int S = (1 << p) - 1; S >= 0; --S)
        {
            for (int G = S; G; G = (G - 1) & S)
                ckmax(dp[u][S], dp[u][S ^ G] + dp[v][G]);
        }
    }
    for (int S = 0; S < (1 << p); ++S)
        dp[u][S] += g[S];
}
signed main()
{
    read(n, p);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= p; ++j)
            read(a[i][j]);
    for (int u = 1; u <= n; ++u)
        for (int S = 0; S < (1 << p); ++S)
            for (int i = 1; i <= p; ++i)
                if ((S >> (i - 1)) & 1)
                    dp[u][S] -= a[u][i];
    read(t);
    for (int i = 1; i <= t; ++i)
    {
        int v, c;
        read(v, c);
        int S = 0;
        while (c--)
        {
            int x;
            read(x);
            S |= 1 << (x - 1);
        }
        int revS = ((1 << p) - 1) ^ S;
        for (int G = revS; G; G = (G - 1) & revS)
            g[S | G] += v;
        g[S] += v;
    }
    dfs(1, 0);
    printf("%lld\n", dp[1][(1 << p) - 1]);
    return 0;
}