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
const int N = 505;
struct Edge
{
    int next, to, dis;
} edge[N * N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
inline void ckmin(int &x, int y)
{
    if (x > y)
        x = y;
}
int n, m, dp[N][N];
int cnt[N];
signed main()
{
    memset(dp, 0x3f, sizeof(dp));
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        dp[u][v] = dp[v][u] = w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i <= n; ++i)
        dp[i][i] = 0;
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                ckmin(dp[i][j], dp[i][k] + dp[k][j]);
    for (int i = 1; i <= n; ++i)
    {
        memset(cnt, 0, sizeof(cnt));
        for (int u = 1; u <= n; ++u)
            for (int e = head[u]; e; e = edge[e].next)
            {
                int &v = edge[e].to;
                if (dp[i][u] + edge[e].dis == dp[i][v])
                    ++cnt[v];
            }
        for (int j = i + 1; j <= n; ++j)
        {
            int res = 0;
            for (int k = 1; k <= n; ++k)
                if (i != k)
                    if (dp[i][j] == dp[i][k] + dp[k][j])
                        res += cnt[k];
            printf("%d ", res);
        }
    }
    putchar('\n');
    return 0;
}