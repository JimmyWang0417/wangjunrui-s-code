#include <algorithm>
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
constexpr int N = 5e5 + 5, M = 45e5 + 5;
int n, m;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
int recycle[N * 2], recycletot;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
    recycle[++recycletot] = from;
}
int dep[N], low[N], dfn[N], dfstime;
int where[N * 2], b[N * 2], Log[N * 2], tot;
int f[N * 2][25];
inline void dfs(int u, int _fa)
{
    dfn[u] = ++dfstime;
    b[where[u] = ++tot] = u;
    dep[u] = dep[_fa] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        b[++tot] = u;
    }
    low[u] = dfstime;
}
inline int calc(int u, int v)
{
    return dep[u] < dep[v] ? u : v;
}
inline int getlca(int u, int v)
{
    u = where[u], v = where[v];
    if (u > v)
        swap(u, v);
    int k = Log[v - u + 1];
    return calc(f[u][k], f[v - (1 << k) + 1][k]);
}
int st[N], top;
inline void insert(int u)
{
    if (top == 0)
    {
        st[++top] = u;
        return;
    }
    int lca = getlca(st[top], u);
    while (top > 1 && dfn[lca] <= dfn[st[top - 1]])
    {
        add_edge(st[top - 1], st[top]);
        add_edge(st[top], st[top - 1]);
        --top;
    }
    if (lca != st[top])
    {
        add_edge(lca, st[top]);
        add_edge(st[top], lca);
        st[top] = lca;
    }
    st[++top] = u;
}
vector<int> g[N];
pair<int, int> a[N];
struct node
{
    int u, v, id;
    node(int _u = 0, int _v = 0, int _id = 0) : u(_u), v(_v), id(_id) {}
};
node p[M], q[M];
vector<node> que[N];
int ptot, qtot;
inline void add(int u, int v)
{
    int lca = getlca(u, v);
    if (v == lca)
        p[++ptot] = node(u, v);
    else if (u == lca)
        q[++qtot] = node(u, v);
    else
    {
        que[lca].emplace_back(node(dfn[u], v, 0));
        que[lca].emplace_back(node(low[u] + 1, v, -2));
    }
}
inline void calc(int u, int _fa, int res, int color, int goal)
{
    if (a[u].second == color)
    {
        if (a[u].first == 1)
            ++res;
        else
        {
            if (res == 1)
            {
                add(goal, u);
                return;
            }
            else
                --res;
        }
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        calc(v, u, res, color, goal);
    }
}
struct tree_array
{
    int c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= dfstime; i += lowbit(i))
            c[i] += val;
    }
    inline void update(int l, int r, int val)
    {
        update(l, val);
        update(r + 1, -val);
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
    inline void clear()
    {
        fill(c + 1, c + 1 + dfstime, 0);
    }
} tree;
int answer[M];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].first, a[i].second);
        g[a[i].second].push_back(i);
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    fill(head + 1, head + 1 + n, recycletot = num_edge = 0);
    Log[0] = -1;
    for (int i = 1; i <= tot; ++i)
    {
        Log[i] = Log[i >> 1] + 1;
        f[i][0] = b[i];
    }
    for (int j = 1; j <= Log[tot]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= tot; ++i)
            f[i][j] = calc(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    for (int kase = 1; kase <= n; ++kase)
    {
        sort(g[kase].begin(), g[kase].end(), [](int x, int y)
             { return dfn[x] < dfn[y]; });
        for (auto u : g[kase])
            insert(u);
        while (top > 1)
        {
            add_edge(st[top - 1], st[top]);
            add_edge(st[top], st[top - 1]);
            --top;
        }
        if (top)
            --top;
        for (auto u : g[kase])
            if (a[u].first == 1)
                calc(u, 0, 0, kase, u);
        while (recycletot)
            head[recycle[recycletot--]] = 0;
        num_edge = 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        int lca = getlca(u, v);
        p[++ptot] = node(u, lca, i);
        q[++qtot] = node(lca, v, i);
        if (u != lca && v != lca)
            que[lca].push_back(node(dfn[u], v, i));
    }
    sort(p + 1, p + 1 + ptot, [](node x, node y)
         { return dep[x.v] == dep[y.v] ? x.id < y.id : dep[x.v] > dep[y.v]; });
    sort(q + 1, q + 1 + qtot, [](node x, node y)
         { return dep[x.u] == dep[y.u] ? x.id < y.id : dep[x.u] > dep[y.u]; });
    for (int i = 1; i <= ptot; ++i)
    {
        if (p[i].id)
            answer[p[i].id] += tree.query(dfn[p[i].u]);
        else
            tree.update(dfn[p[i].u], low[p[i].u], 1);
    }
    tree.clear();
    for (int i = 1; i <= qtot; ++i)
    {
        if (q[i].id)
            answer[q[i].id] += tree.query(dfn[q[i].v]);
        else
            tree.update(dfn[q[i].v], low[q[i].v], 1);
    }
    tree.clear();
    for (int u = 1; u <= n; ++u)
    {
        sort(que[u].begin(), que[u].end(), [](node x, node y)
             { return x.u == y.u ? x.id < y.id : x.u < y.u; });
        for (auto v : que[u])
            if (v.id > 0)
                answer[v.id] += tree.query(dfn[v.v]);
            else
                tree.update(dfn[v.v], low[v.v], v.id + 1);
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}