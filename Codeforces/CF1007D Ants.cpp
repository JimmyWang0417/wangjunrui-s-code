// Problem: D. Ants
// Contest: Codeforces - Codeforces Round #497 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1007/D
// Memory Limit: 768 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 1e5 + 5, M = 6e6 + 10;
int n, m;
vector<int> g[M];
int tot;
class treechain
{
public:
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
    int size[N], son[N];
    int dep[N], fa[N];
    inline void dfs1(int u, int _fa)
    {
        size[u] = 1;
        fa[u] = _fa;
        dep[u] = dep[_fa] + 1;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (v == _fa)
                continue;
            dfs1(v, u);
            size[u] += size[v];
            if (size[son[u]] < size[v])
                son[u] = v;
        }
    }
    int dfn[N], dfstime;
    int top[N];
    inline void dfs2(int u, int topf)
    {
        top[u] = topf;
        dfn[u] = ++dfstime;
        if (son[u])
            dfs2(son[u], topf);
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (top[v])
                continue;
            dfs2(v, v);
        }
    }
    vector<int> tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    inline void update(int rt, int l, int r, int x, int y, int val)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].push_back(val);
        int mid = (l + r) >> 1;
        update(lc, l, mid, x, y, val);
        update(rc, mid + 1, r, x, y, val);
    }
    inline void update(int x, int y, int val)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            update(1, 1, n, dfn[top[x]], dfn[x], val);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        if (dfn[x] < dfn[y])
            update(1, 1, n, dfn[x] + 1, dfn[y], val);
    }
    inline void add(int x, int y)
    {
        g[x].push_back(y);
        g[y ^ 1].push_back(x ^ 1);
    }
    inline void solve(int rt, int l, int r, int las)
    {
        int ql = ++tot, qr = (tot += (int)tree[rt].size());
        if (ql < qr)
            add((qr - 1) << 1, qr << 1);
        else if (las)
            add(las << 1, ql << 1);
        for (int i = 0; i < (int)tree[rt].size(); ++i)
        {
            int u = tree[rt][i];
            add(u, (ql + i) << 1);
            if (i > 0)
            {
                add((ql + i - 1) << 1, (ql + i) << 1);
                add((ql + i - 1) << 1, u ^ 1);
            }
            else if (las)
            {
                add(las << 1, ql << 1);
                add(las << 1, u ^ 1);
            }
        }
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        solve(lc, l, mid, qr);
        solve(rc, mid + 1, r, qr);
    }
    inline void init()
    {
        read(n);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            read(u, v);
            add_edge(u, v);
            add_edge(v, u);
        }
        dfs1(1, 0);
        dfs2(1, 1);
        read(m);
        tot = m;
        for (int i = 1; i <= m; ++i)
        {
            int a, b, c, d;
            read(a, b, c, d);
            update(a, b, i << 1);
            update(c, d, i << 1 | 1);
        }
        solve(1, 1, n, 0);
    }
} tree;
int dfn[M], low[M], dfstime;
int st[M], top;
int belong[M], color;
inline void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    for (auto v : g[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            ckmin(low[u], low[v]);
        }
        else if (!belong[v])
            ckmin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        belong[u] = ++color;
        while (st[top] != u)
            belong[st[top--]] = color;
        --top;
    }
}
signed main()
{
    tree.init();
    for (int i = 1; i <= (tot << 1 | 1); ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= m; ++i)
        if (belong[i << 1] == belong[i << 1 | 1])
        {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");
    for (int i = 1; i <= m; ++i)
        puts(belong[i << 1] < belong[i << 1 | 1] ? "1" : "2");
    return 0;
}