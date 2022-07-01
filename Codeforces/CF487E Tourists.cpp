#include <climits>
#include <cstdio>
#include <set>
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
int n, m, q, a[N];
int dfn[N], low[N], dfstime;
int st[N], top;
int tot;
vector<int> g[N], h[N];
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
            if (dfn[u] == low[v])
            {
                ++tot;
                h[tot].push_back(u);
                h[u].push_back(tot);
                while (st[top] != v)
                {
                    h[tot].push_back(st[top]);
                    h[st[top]].push_back(tot);
                    --top;
                }
                h[tot].push_back(v);
                h[v].push_back(tot);
                --top;
            }
        }
        else
            ckmin(low[u], dfn[v]);
    }
}
int dep[N], fa[N];
int size[N], son[N];
inline void dfs1(int u, int _fa)
{
    dep[u] = dep[fa[u] = _fa] + 1;
    size[u] = 1;
    for (auto v : h[u])
    {
        if (v == _fa)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
int topfa[N];
int rk[N];
inline void dfs2(int u, int topf)
{
    rk[dfn[u] = ++dfstime] = u;
    topfa[u] = topf;
    if (son[u])
        dfs2(son[u], topf);
    for (auto v : h[u])
    {
        if (topfa[v])
            continue;
        dfs2(v, v);
    }
}
int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt] = min(tree[lc], tree[rc]);
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt] = a[rk[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos)
{
    if (l == r)
    {
        tree[rt] = a[rk[l]];
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos);
    else
        update(rc, mid + 1, r, pos);
    pushup(rt);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return INT_MAX;
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    return min(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
inline int query(int x, int y)
{
    int res = INT_MAX;
    while (topfa[x] != topfa[y])
    {
        if (dep[topfa[x]] < dep[topfa[y]])
            swap(x, y);
        ckmin(res, query(1, 1, dfstime, dfn[topfa[x]], dfn[x]));
        x = fa[topfa[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ckmin(res, query(1, 1, dfstime, dfn[x], dfn[y]));
    if (x > n)
        ckmin(res, a[fa[x]]);
    return res;
}
multiset<int> se[N];
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
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
    dfstime = 0;
    for (int i = 1; i <= tot; ++i)
        if (!dep[i])
        {
            dfs1(i, 0);
            dfs2(i, i);
        }
    for (int i = 1; i <= n; ++i)
    {
        if (fa[i])
            se[fa[i]].insert(a[i]);
    }
    for (int i = n + 1; i <= tot; ++i)
        a[i] = *se[i].begin();
    build(1, 1, dfstime);
    for (int i = 1; i <= q; ++i)
    {
        static char opt[5];
        scanf("%s", opt);
        int x, y;
        read(x, y);
        if (opt[0] == 'C')
        {
            if (fa[x])
            {
                se[fa[x]].erase(a[x]);
                se[fa[x]].insert(y);
                a[fa[x]] = *se[fa[x]].begin();
                update(1, 1, dfstime, dfn[fa[x]]);
            }
            a[x] = y;
            update(1, 1, dfstime, dfn[x]);
        }
        else
            printf("%d\n", query(x, y));
    }
    return 0;
}