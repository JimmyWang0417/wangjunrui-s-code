#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 1e5 + 5;
constexpr int BLOCK = sqrt(N) + 10;
int n, q;
int block, num;
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
int f[N][BLOCK];
int g[N][BLOCK];
int h[BLOCK];
int size[N];
inline void dfs(int u, int _fa)
{
    size[u] = 1;
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        for (int i = 0; i <= block; ++i)
            f[u][i] += max(1, f[v][i] - i);
        memcpy(h, g[u], sizeof(g[u]));
        memset(g[u], 0, sizeof(g[u]));
        for (int i = 0; i < size[u] && i < num; ++i)
        {
            ckmax(g[u][i], h[i] + 1);
            for (int j = 0; i + j < num && j < size[v]; ++j)
                ckmax(g[u][i + j + 1], h[i] + g[v][j]);
        }
        size[u] += size[v];
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
#endif
    read(n);
    block = (int)sqrt(n);
    num = (n - 1) / block + 1 + 5;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    read(q);
    while (q--)
    {
        int u, k;
        read(u, k);
        if (k <= block)
            printf("%d\n", f[u][k]);
        else
        {
            int res = 0;
            for (int i = 0; i < num; ++i)
                ckmax(res, g[u][i] - i * k);
            printf("%d\n", res);
        }
    }
    return 0;
}