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
const int N = 1e5 + 5;
int n, m, a[N];
int minn[N];
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
int fa[N][25], dis[N][25], cnt[N];
int sum, root, size[N], maxsize[N];
bool vis[N];
inline void getroot(int u, int _fa)
{
    size[u] = 1;
    maxsize[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        getroot(v, u);
        size[u] += size[v];
        ckmax(maxsize[u], size[v]);
    }
    ckmax(maxsize[u], sum - size[u]);
    if (maxsize[root] > maxsize[u])
        root = u;
}
inline void dfs(int u, int _fa, int d)
{
    size[u] = 1;
    ++cnt[u];
    dis[u][cnt[u]] = d, fa[u][cnt[u]] = root;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        dfs(v, u, d + 1);
        size[u] += size[v];
    }
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    dfs(u, 0, 0);
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = size[v];
        solve(v);
    }
}
inline void update(int u)
{
    for (int i = cnt[u]; i >= 1; --i)
        ckmin(minn[fa[u][i]], dis[u][i]);
}
inline int query(int u)
{
    int res = INT_MAX;
    for (int i = cnt[u]; i >= 1; --i)
        ckmin(res, minn[fa[u][i]] + dis[u][i]);
    return res;
}
signed main()
{
    memset(minn, 0x3f, sizeof(minn));
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    maxsize[root = 0] = sum = n;
    solve(1);
    update(1);
    for (int i = 1; i <= m; ++i)
    {
        int opt, u;
        read(opt, u);
        if (opt == 1)
            update(u);
        else
            printf("%d\n", query(u));
    }
    return 0;
}