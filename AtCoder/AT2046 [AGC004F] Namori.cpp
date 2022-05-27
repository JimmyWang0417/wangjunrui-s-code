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
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
int dp[N], dep[N];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[fa[u] = _fa] + 1;
    if (dep[u] & 1)
        ++dp[u];
    else
        --dp[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        dp[u] += dp[v];
    }
}
int p[N], tot;
signed main()
{
    read(n, m);
    int root = 1, cor = 0;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        if (find(x) == find(y))
        {
            root = x;
            cor = y;
            continue;
        }
        fa[find(x)] = find(y);
        add_edge(x, y);
        add_edge(y, x);
    }
    memset(fa, 0, sizeof(fa));
    dfs(root, 0);
    if (n - 1 == m)
    {
        if (dp[root])
            printf("-1\n");
        else
        {
            int res = 0;
            for (int i = 1; i <= n; ++i)
                res += abs(dp[i]);
            printf("%d\n", res);
        }
    }
    else
    {
        if (dep[cor] & 1)
        {
            if (dp[root] & 1)
                printf("-1\n");
            else
            {
                for (int x = cor; x; x = fa[x])
                    dp[x] -= dp[root] / 2;
                int res = 0;
                for (int i = 1; i <= n; ++i)
                    res += abs(dp[i]);
                printf("%d\n", res);
            }
        }
        else
        {
            if (dp[root])
                printf("-1\n");
            else
            {
                for (int x = cor; x; x = fa[x])
                    p[++tot] = dp[x];
                int mid = (tot + 1) / 2;
                nth_element(p + 1, p + mid, p + 1 + tot);
                for (int x = cor; x; x = fa[x])
                    dp[x] -= p[mid];
                int res = 0;
                for (int i = 1; i <= n; ++i)
                    res += abs(dp[i]);
                printf("%d\n", res);
            }
        }
    }
    return 0;
}