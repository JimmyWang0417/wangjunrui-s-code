#include <cstdio>
#include <vector>
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
constexpr int N = 2e5 + 5;
int n, m, q;
vector<int> g[N], h[N];
int tot;
int dfn[N], low[N], dfstime;
int st[N], top;
inline void tarjan(int u)
{
    st[++top] = u;
    dfn[u] = low[u] = ++dfstime;
    for (auto v : g[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            ckmin(low[u], low[v]);
            if (dfn[u] == low[v])
            {
                ++tot;
                while (st[top] != v)
                {
                    h[tot].push_back(st[top]);
                    h[st[top]].push_back(tot);
                    --top;
                }
                h[tot].push_back(st[top]);
                h[st[top]].push_back(tot);
                --top;
                h[tot].push_back(u);
                h[u].push_back(tot);
            }
        }
        else
            ckmin(low[u], dfn[v]);
    }
}
int fa[N][25], dep[N];
inline void dfs1(int u, int _fa)
{
    dep[u] = dep[fa[u][0] = _fa] + 1;
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (auto v : h[u])
    {
        if (v == _fa)
            continue;
        dfs1(v, u);
    }
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
int a[N];
inline void dfs2(int u, int _fa)
{
    for (auto v : h[u])
    {
        if (v == _fa)
            continue;
        dfs2(v, u);
        a[u] += a[v];
    }
}
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    tot = n;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= tot; ++i)
        if (!dep[i])
            dfs1(i, 0);
    for (int i = 1; i <= q; ++i)
    {
        int u, v;
        read(u, v);
        int lca = getlca(u, v);
        ++a[u], ++a[v];
        --a[lca], --a[fa[lca][0]];
    }
    for (int i = 1; i <= tot; ++i)
        if (!fa[i][0])
            dfs2(i, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", a[i]);
    return 0;
}