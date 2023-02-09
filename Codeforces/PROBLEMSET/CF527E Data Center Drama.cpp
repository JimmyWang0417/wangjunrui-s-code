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
constexpr int N = 1e5 + 5, M = 6e5 + 5;
int n, m;
struct Edge
{
    int next, to;
} edge[M];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
bool vis[M];
int cnt;
inline void dfs(int u)
{
    for (int &i = head[u]; i; i = edge[i].next)
        if (!vis[i])
        {
            int &v = edge[i].to;
            vis[i] = vis[i ^ 1] = true;
            dfs(v);
            if (++cnt & 1)
                printf("%d %d\n", u, v);
            else
                printf("%d %d\n", v, u);
        }
}
int deg[N];
int p[N], tot;
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
        ++deg[u], ++deg[v];
    }
    for (int i = 1; i <= n; ++i)
        if (deg[i] & 1)
            p[++tot] = i;
    for (int i = 1; i <= tot; i += 2)
    {
        add_edge(p[i], p[i + 1]);
        add_edge(p[i + 1], p[i]);
        ++m;
    }
    if (m & 1)
    {
        add_edge(1, 1);
        add_edge(1, 1);
        ++m;
    }
    printf("%d\n", m);
    dfs(1);
    return 0;
}