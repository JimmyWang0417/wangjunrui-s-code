#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
using namespace std;
const int N = 1e5 + 5;
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int n, m;
int fa[N];
string a[N];
int size[N], son[N], dep[N];
inline void initdfs(int u)
{
    size[u] = 1;
    dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        initdfs(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
set<string> se[N];
inline void add(const string &val, int de)
{
    se[de].insert(val);
}
inline void del(const string &val, int de)
{
    se[de].erase(val);
}
inline void addtree(int u)
{
    add(a[u], dep[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        addtree(v);
    }
}

inline void deltree(int u)
{
    se[dep[u]].clear();
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        deltree(v);
    }
}
int answer[N];
vector<pair<int, int>> g[N];
inline void dfs(int u, bool keep)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == son[u])
            continue;
        dfs(v, false);
    }
    if (son[u])
        dfs(son[u], true);
    add(a[u], dep[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == son[u])
            continue;
        addtree(v);
    }
    for (auto v : g[u])
        answer[v.first] = v.second <= n ? (int)se[v.second].size() : 0;
    if (!keep)
        deltree(u);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i] >> fa[i];
        add_edge(fa[i], i);
    }
    for (int i = 1; i <= n; ++i)
        if (!fa[i])
            initdfs(i);
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        int u, k;
        cin >> u >> k;
        g[u].push_back(make_pair(i, dep[u] + k));
    }
    for (int i = 1; i <= n; ++i)
        if (!fa[i])
            dfs(i, false);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}
