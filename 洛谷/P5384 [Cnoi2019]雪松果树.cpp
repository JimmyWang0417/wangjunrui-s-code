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
const int N = 1e6 + 5;
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
int size[N], son[N];
int dfn[N], id[N], dfstime, top[N], fa[N];
int dep[N];
inline void initdfs1(int u)
{
    size[u] = 1;
    dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        initdfs1(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
inline void initdfs2(int u, int topf)
{
    id[dfn[u] = ++dfstime] = u;
    top[u] = topf;
    if (!son[u])
        return;
    initdfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (top[v])
            continue;
        initdfs2(v, v);
    }
}
inline int jump(int u, int k)
{
    int d = dep[u] - k;
    while (dep[top[u]] > d)
        u = fa[top[u]];
    return id[dfn[u] + d - dep[u]];
}
int answer[N];
vector<pair<int, int>> g[N];
int cnt[N];
inline void addtree(int u)
{
    ++cnt[dep[u]];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        addtree(v);
    }
}
inline void deltree(int u)
{
    --cnt[dep[u]];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        deltree(v);
    }
}
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
    ++cnt[dep[u]];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == son[u])
            continue;
        addtree(v);
    }
    for (auto v : g[u])
        answer[v.first] = cnt[v.second] - 1;
    if (!keep)
        deltree(u);
}
signed main()
{
    read(n, m);
    for (int i = 2; i <= n; ++i)
    {
        read(fa[i]);
        add_edge(fa[i], i);
    }
    initdfs1(1);
    initdfs2(1, 1);
    //	for(int i=1; i<=n; ++i)
    //		printf("%d ",son[i]);
    //	putchar('\n');
    for (int i = 1; i <= m; ++i)
    {
        int v, p;
        read(v, p);
        if (p >= dep[v])
            continue;
        g[jump(v, p)].push_back(make_pair(i, dep[v]));
        //		printf(" %d %d %d\n",jump(v,p),i,dep[v]);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; ++i)
        printf("%d ", answer[i]);
    putchar('\n');
    return 0;
}
