#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e5 + 5;
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
int n, m;
int Log[N];
int fa[N][20], dep[N];
int size[N];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    fa[u][0] = _fa;
    size[u] = 1;
    for (int i = 0; i < Log[dep[u]]; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        size[u] += size[v];
    }
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
inline int jump(int u, int k)
{
    for (int i = Log[k]; i >= 0; --i)
        if ((k >> i) & 1)
            u = fa[u][i];
    return u;
}
signed main()
{
    read(n);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
        Log[i] = Log[i >> 1] + 1;
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        read(x, y);
        add_edge(x, y);
        add_edge(y, x);
    }
    dfs(1, 0);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        if (u == v)
        {
            printf("%d\n", n);
            continue;
        }
        if (dep[u] < dep[v])
            swap(u, v);
        int lca = getlca(u, v), d = dep[u] + dep[v] - dep[lca] * 2;
        if (d & 1)
            puts("0");
        else
        {
            int x = jump(u, d / 2);
            if (x == lca)
                printf("%d\n", n - size[jump(u, dep[u] - dep[x] - 1)] - size[jump(v, dep[v] - dep[x] - 1)]);
            else
                printf("%d\n", size[x] - size[jump(u, dep[u] - dep[x] - 1)]);
        }
    }
    return 0;
}
