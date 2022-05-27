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
const int N = 1e5 + 5, M = 1e6 + 5;
struct Edge
{
    int next, to;
} edge[M];
int head[N], num_edge;
int in[N];
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
vector<int> g[N];
int n;
int fa[N][25], dep[N];
int Log[N];
inline void dfs(int u, int _fa)
{
    //	printf("%d %d\n",u,_fa);
    dep[u] = dep[_fa] + 1;
    fa[u][0] = _fa;
    for (int i = 0; i < Log[dep[u]]; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
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
int q[N], hea = 1, tail;
int size[N];
signed main()
{
    read(n);
    Log[0] = -1;
    for (int u = 1; u <= n; ++u)
    {
        Log[u] = Log[u >> 1] + 1;
        int v;
        while (read(v), v)
        {
            g[u].push_back(v);
            add_edge(v, u);
            ++in[u];
        }
    }
    for (int u = 1; u <= n; ++u)
        if (g[u].empty())
        {
            add_edge(0, u);
            ++in[u];
            g[u].push_back(0);
        }
    q[++tail] = 0;
    while (hea <= tail)
    {
        int u = q[hea++];
        if (g[u].empty())
            dfs(u, 0);
        else
        {
            if (g[u].size() == 1u)
                dfs(u, g[u].front());
            else
            {
                int lca = getlca(g[u][0], g[u][1]);
                for (int i = 2; i < (int)g[u].size(); ++i)
                    lca = getlca(lca, g[u][i]);
                dfs(u, lca);
            }
        }
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            //			printf("%d\n",v);
            if (!--in[v])
                q[++tail] = v;
        }
    }
    for (int i = tail; i; --i)
    {
        const int &u = q[i];
        size[fa[u][0]] += size[u] + 1;
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", size[i]);
    return 0;
}
