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
list<int> g[N];
class Tree
{
public:
    int dep[N], fa[N];
    int size[N], son[N];
    inline void dfs1(int u, int _fa)
    {
        fa[u] = _fa;
        dep[u] = dep[_fa] + 1;
        size[u] = 1;
        for (auto v : g[u])
        {
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
        dfn[u] = ++dfstime;
        top[u] = topf;
        if (son[u])
            dfs2(son[u], topf);
        for (auto v : g[u])
        {
            if (top[v])
                continue;
            dfs2(v, v);
        }
    }
    struct node
    {
        int lcolor, rcolor;
        int ans;
        node(int _x = 0, int _y = 0, int _ans = -1) : lcolor(_x), rcolor(_y), ans(_ans) {}
        inline node operator+(const node &rhs) const
        {
            if (ans == -1)
                return rhs;
            if (rhs.ans == -1)
                return (*this);
            return node(lcolor, rhs.rcolor, ans + rhs.ans + (rcolor != rhs.lcolor));
        }
    } tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    inline void pushup(int rt)
    {
        tree[rt] = tree[lc] + tree[rc];
    }
    inline void build(int rt, int l, int r)
    {
        if (l == r)
        {
            tree[rt].ans = tree[rt].lcolor = tree[rt].rcolor = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(rt);
    }
    inline void update(int rt, int l, int r, int pos, int val)
    {
        if (l == r)
        {
            tree[rt].lcolor = tree[rt].rcolor = val;
            tree[rt].ans = 0;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc, l, mid, pos, val);
        else
            update(rc, mid + 1, r, pos, val);
        pushup(rt);
    }
    inline node query(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return node();
        if (x <= l && r <= y)
            return tree[rt];
        int mid = (l + r) >> 1;
        return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
    }
    inline int query(int x, int y)
    {
        node L, R;
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
            {
                swap(x, y);
                swap(L, R);
            }
            L = query(1, 1, n, dfn[top[x]], dfn[x]) + L;
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
        {
            swap(x, y);
            swap(L, R);
        }
        swap(L.lcolor, L.rcolor);
        return (L + query(1, 1, n, dfn[x], dfn[y]) + R).ans;
    }
    inline void init()
    {
        dfs1(1, 0);
        dfs2(1, 1);
        build(1, 1, n);
    }
} tree;
int size[N], son[N];
int lasedge[N];
inline void init(int u, int _fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        lasedge[v] = i;
        init(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
inline void update(int u, int _fa, int val)
{
    tree.update(1, 1, n, tree.dfn[u], val);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        update(v, u, val);
    }
}
int answer[N];
inline void solve(int u, int _fa, bool del)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || v == son[u])
            continue;
        solve(v, u, true);
    }
    if (son[u])
        solve(son[u], u, false);
    tree.update(1, 1, n, tree.dfn[u], 1);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || v == son[u])
            continue;
        update(v, u, 1);
    }
    if (lasedge[u])
        answer[(lasedge[u] + 1) / 2] = tree.query(u, _fa);
    if (del)
        update(u, _fa, 0);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("exchange.in", "r", stdin);
    freopen("exchange.out", "w", stdout);
#endif
    read(n);
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
    tree.init();
    init(1, 0);
    solve(1, 0, false);
    for (int i = 1; i < n; ++i)
        printf("%d ", answer[i]);
    putchar('\n');
    return 0;
}