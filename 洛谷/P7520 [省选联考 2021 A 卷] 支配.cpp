#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 3e3 + 5, M = 2e4 + 5;
int n, m, q;
vector<int> g[N], revg[N], h[N];
bool vis[N][N], exist[N][N];
int fa[N];
int p[N];
inline void dfs(int u, int goal)
{
    if (vis[goal][u])
        return;
    if (u == goal)
        return;
    vis[goal][u] = true;
    for (auto v : g[u])
        dfs(v, goal);
}
inline void solve(int u, int goal, int del)
{
    if (u == del)
        return;
    if (exist[goal][u])
        return;
    exist[goal][u] = true;
    for (auto v : revg[u])
        solve(v, goal, del);
}
bool mp[N];
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        revg[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
    {
        p[i] = i;
        dfs(1, i);
        for (int j = 1; j <= n; ++j)
            if (vis[0][j] && !vis[i][j])
                h[j].push_back(i);
    }
    sort(p + 1, p + 1 + n, [](int x, int y) { return h[x].size() < h[y].size(); });
    for (int u = 1; u <= n; ++u)
    {
        for (auto v : h[u])
            if (h[v].size() + 1 == h[u].size())
                fa[u] = v;
    }
    for (int i = 2; i <= n; ++i)
        solve(i, i, fa[i]);
    for (int i = 1; i <= q; ++i)
    {
        int u, v;
        read(u, v);
        for (int j = 1; j <= n; ++j)
            if (vis[fa[j]][u] && exist[j][v])
                mp[j] = true;
        for (int j = 1; j <= n; ++j)
            if (mp[fa[p[j]]])
                mp[p[j]] = true;
        int res = 0;
        for (int j = 1; j <= n; ++j)
            if (mp[j])
                ++res;
        memset(mp, 0, sizeof(mp));
        printf("%d\n", res);
    }
    return 0;
}