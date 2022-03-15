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
int n, m, q, a[N];
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
int belong[N];
int dep[N];
int maxchain[N];
vector<int> g[N];
vector<ll> sumg[N];
int maxid[N], nxtmaxid[N];
inline void dfs1(int u, int goal)
{
    belong[u] = goal;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (belong[v])
            continue;
        dfs1(v, goal);
        if (dep[v] > dep[maxid[u]])
        {
            nxtmaxid[u] = maxid[u];
            maxid[u] = v;
        }
        else if (dep[v] > dep[nxtmaxid[u]])
            nxtmaxid[u] = v;
    }
    dep[u] = dep[maxid[u]] + 1;
    ckmax(maxchain[goal], dep[u] + dep[nxtmaxid[u]] + 1);
}
int maxlen[N];
inline void dfs2(int u, int _fa, int maxx)
{
    maxlen[u] = dep[u];
    ckmax(maxlen[u], maxx);
    g[belong[u]].push_back(maxlen[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to, w = (maxid[u] == v) ? nxtmaxid[u] : maxid[u];
        if (v == _fa)
            continue;
        dfs2(v, u, max(maxx, dep[w] + 1) + 1);
    }
}
map<pair<int, int>, double> mp;
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dep[0] = -1;
    for (int i = 1; i <= n; ++i)
        if (!belong[i])
        {
            dfs1(i, i);
            dfs2(i, 0, 0);
            sort(g[i].begin(), g[i].end());
            sumg[i].resize(g[i].size());
            sumg[i][sumg[i].size() - 1] = g[i][sumg[i].size() - 1];
            for (int j = (int)sumg[i].size() - 2; j >= 0; --j)
                sumg[i][j] += sumg[i][j + 1] + g[i][j];
        }
    for (int i = 1; i <= q; ++i)
    {
        int x, y;
        read(x, y);
        x = belong[x], y = belong[y];
        if (x == y)
            printf("-1\n");
        else
        {
            int res = max(maxchain[x], maxchain[y]);
            ll ans = 0;
            if (g[x].size() > g[y].size())
                swap(x, y);
            if (mp.count(make_pair(x, y)))
            {
                printf("%.15lf\n", mp[make_pair(x, y)]);
                continue;
            }
            for (auto u : g[x])
            {
                int it = (int)(lower_bound(g[y].begin(), g[y].end(), res - u - 1) - g[y].begin());
                ans += (ll)it * res + sumg[y][it] + (ll)(g[y].size() - it) * (u + 1);
            }
            printf("%.15lf\n", mp[make_pair(x, y)] = (double)ans / (double)g[x].size() / (double)g[y].size());
        }
    }
    return 0;
}