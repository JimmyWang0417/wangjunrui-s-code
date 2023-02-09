#include <algorithm>
#include <cstdio>
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
constexpr int N = 1e6 + 5;
int n, m, q, a[N];
struct node
{
    int u, v, w;
} b[N];
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
int rk[N], dfn[N], low[N], dfstime;
int fa[N][25];
int color[N];
inline void dfs(int u)
{
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    rk[dfn[u] = ++dfstime] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        fa[v][0] = u;
        dfs(v);
    }
    low[u] = dfstime;
}
inline int query(int u, int v)
{
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] && color[fa[u][i]] >= v)
            u = fa[u][i];
    return u;
}
int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt] = a[tree[lc]] > a[tree[rc]] ? tree[lc] : tree[rc];
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt] = rk[l] <= n ? rk[l] : 0;
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
        tree[rt] = 0;
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
        return 0;
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    int la = query(lc, l, mid, x, y), ra = query(rc, mid + 1, r, x, y);
    return a[la] > a[ra] ? la : ra;
}
struct Query
{
    int x, y;
} c[N];
int father[N];
inline int find(int x)
{
    return !father[x] ? x : father[x] = find(father[x]);
}
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
    {
        read(b[i].u, b[i].v);
        b[i].w = q + 1;
    }
    for (int i = 1; i <= q; ++i)
    {
        read(c[i].x, c[i].y);
        if (c[i].x == 2)
            b[c[i].y].w = i;
    }
    sort(b + 1, b + 1 + m, [](const node &x, const node &y)
         { return x.w > y.w; });
    int cnt = n;
    for (int i = 1; i <= m; ++i)
    {
        int u = find(b[i].u), v = find(b[i].v);
        if (u != v)
        {
            ++cnt;
            add_edge(cnt, u), add_edge(cnt, v);
            father[u] = father[v] = cnt;
            color[cnt] = b[i].w;
        }
    }
    for (int i = 1; i <= cnt; ++i)
        if (find(i) == i)
            dfs(i);
    build(1, 1, dfstime);
    for (int i = 1; i <= q; ++i)
    {
        if (c[i].x == 1)
        {
            int u = query(c[i].y, i);
            int pos = query(1, 1, dfstime, dfn[u], low[u]);
            printf("%d\n", a[pos]);
            if (pos)
                update(1, 1, dfstime, dfn[pos]);
        }
    }
    return 0;
}