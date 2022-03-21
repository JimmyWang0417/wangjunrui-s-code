#include <cstdio>
#include <list>
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
constexpr int N = 1e5 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, m;
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
    dep[u] = dep[fa[u] = _fa] + 1;
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
int dfn[N], low[N], dfstime;
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
    low[u] = dfstime;
}
inline int getlca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}
struct node
{
    int ans;
    ll cnt;
    node(int _ans = 0, ll _cnt = 0) : ans(_ans), cnt(_cnt) {}
    inline node operator+(const node &rhs) const
    {
        node res = (*this);
        if (res.ans > rhs.ans)
            res = rhs;
        else if (res.ans == rhs.ans)
            res.cnt += rhs.cnt;
        return res;
    }
};
struct Tree
{
    node hist, now, tag;
    int add, time;
    inline void update(int val1, node val2)
    {
        tag = tag + node(add + val2.ans, val2.cnt);
        hist = hist + node(now.ans + val2.ans, now.cnt * val2.cnt);
        now.ans += val1;
        add += val1;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
int nowtime;
pair<int, Tree> restore[N * 100];
int tot;
inline void recycle(int rt)
{
    if (tree[rt].time == nowtime)
        return;
    restore[++tot] = make_pair(rt, tree[rt]);
    tree[rt].time = nowtime;
}
inline void pushup(int rt)
{
    tree[rt].now = tree[lc].now + tree[rc].now;
    tree[rt].hist = tree[lc].hist + tree[rc].hist;
}
inline void pushdown(int rt)
{
    if (tree[rt].add || tree[rt].tag.cnt)
    {
        recycle(lc), recycle(rc);
        tree[lc].update(tree[rt].add, tree[rt].tag);
        tree[rc].update(tree[rt].add, tree[rt].tag);
        tree[rt].tag = node(0, 0);
        tree[rt].add = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].hist = tree[rt].now = node(1, 1);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    recycle(rt);
    if (x <= l && r <= y)
        return tree[rt].update(val, node(val, 1));
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].hist.ans <= 1 ? tree[rt].hist.cnt : 0;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
inline ll query0(int x, int y)
{
    ll res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        res += query(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return res + query(1, 1, n, dfn[x], dfn[y]);
}
inline ll query1(int x, int y)
{
    ll res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        res += query(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return res + query(1, 1, n, dfn[x] + 1, dfn[y]);
}
ll answer[N];
list<int> g[N], que[N], task[N];
pair<int, int> a[N];
bool exist[N];
inline void calc(int u, int _fa, int goal)
{
    ++nowtime;
    int las = tot;
    exist[u] = true;
    update(1, 1, n, dfn[goal], low[goal], 1);
    for (auto v : g[u])
    {
        if (exist[v])
            update(1, 1, n, dfn[goal], low[goal], -1);
        else if (dfn[goal] <= dfn[v] && dfn[v] <= low[goal])
            update(1, 1, n, dfn[v], low[v], -1);
    }
    for (auto i : task[u])
        answer[i] += query1(goal, a[i].first);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        calc(v, u, goal);
    }
    while (tot > las)
    {
        tree[restore[tot].first] = restore[tot].second;
        --tot;
    }
    exist[u] = false;
    --nowtime;
}
inline void solve(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        solve(v, u);
    }
    update(1, 1, n, dfn[u] + 1, low[u], 1);
    for (auto v : g[u])
    {
        if (dfn[u] <= dfn[v] && dfn[v] <= low[u])
            update(1, 1, n, dfn[v], low[v], -1);
    }
    for (auto i : que[u])
    {
        answer[i] = query0(u, a[i].second);
        task[a[i].second].push_back(i);
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || v == son[u])
            continue;
        calc(v, u, u);
    }
    for (auto i : que[u])
        task[a[i].second].clear();
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("letyoudown.in", "r", stdin);
    freopen("letyoudown.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int &u = a[i].first, &v = a[i].second;
        read(u, v);
        if (dfn[u] > dfn[v])
            swap(u, v);
        que[getlca(u, v)].push_back(i);
    }
    solve(1, 0);
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}
