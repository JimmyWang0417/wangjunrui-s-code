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
int answer[N];
int cnt[N];
int size[N], son[N];
inline void init(int u, int _fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        init(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
inline void add(int val)
{
    ++answer[++cnt[val]];
}
inline void del(int val)
{
    --answer[cnt[val]--];
}
inline void addtree(int u, int _fa)
{
    add(a[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        addtree(v, u);
    }
}
inline void deltree(int u, int _fa)
{
    del(a[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        deltree(v, u);
    }
}
list<pair<int, int>> g[N];
int queryanswer[N];
inline void dfs(int u, int _fa, bool exist)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || v == son[u])
            continue;
        dfs(v, u, false);
    }
    if (son[u])
        dfs(son[u], u, true);
    add(a[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || v == son[u])
            continue;
        addtree(v, u);
    }
    for (auto v : g[u])
        queryanswer[v.second] = answer[v.first];
    if (!exist)
        deltree(u, _fa);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(make_pair(v, i));
    }
    init(1, 0);
    dfs(1, 0, true);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", queryanswer[i]);
    return 0;
}