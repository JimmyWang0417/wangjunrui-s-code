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
const int N = 4e4 + 5;
int n, m, q;
struct Tree_array
{
    int sum[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            sum[i] += val;
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
            res += sum[i];
        return res;
    }
} tree;
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

int dfstime;
pair<int, int> dfn[N];
int top[N], dep[N], fa[N];
int size[N], son[N];
inline void dfs1(int u, int _fa)
{
    fa[u] = _fa;
    dep[u] = dep[_fa] + 1;
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
}
inline void dfs2(int u, int topf)
{
    top[u] = topf;
    dfn[u].first = ++dfstime;
    if (son[u])
        dfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (top[v])
            continue;
        dfs2(v, v);
    }
    dfn[u].second = dfstime;
}
inline int getlca(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    return u;
}
inline int jump(int u, int v)
{
    while (top[u] != top[v])
    {
        if (fa[top[u]] == v)
            return top[u];
        u = fa[top[u]];
    }
    return son[v];
}
struct Matrix
{
    int x, l, r, c, v;
    Matrix(int _x = 0, int _l = 0, int _r = 0, int _c = 0, int _v = 0) : x(_x), l(_l), r(_r), c(_c), v(_v) {}
    inline bool operator<(const Matrix &rhs) const
    {
        return x < rhs.x;
    }
} a[N * 4], a1[N * 4], a2[N * 4];
int cnt;
struct Query
{
    int x, y, k, id;
    inline bool operator<(const Query &rhs) const
    {
        return x < rhs.x;
    }
} b[N], b1[N], b2[N];
int p[N], tot;
int answer[N];
inline void solve(int cl, int cr, int ql, int qr, int l, int r)
{
    //	printf("%d %d %d %d %d %d\n",cl,cr,ql,qr,l,r);
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; ++i)
            answer[b[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1;
    int j = cl;
    int cnta1 = 0, cnta2 = 0, cntb1 = 0, cntb2 = 0;
    for (int i = ql; i <= qr; ++i)
    {
        for (; j <= cr && a[j].x <= b[i].x; ++j)
        {
            if (a[j].c <= p[mid])
            {
                tree.update(a[j].l, a[j].r, a[j].v);
                a1[++cnta1] = a[j];
            }
            else
                a2[++cnta2] = a[j];
        }
        int now = tree.query(b[i].y);
        if (b[i].k <= now)
            b1[++cntb1] = b[i];
        else
        {
            b[i].k -= now;
            b2[++cntb2] = b[i];
        }
    }
    for (; j <= cr; ++j)
        if (a[j].c <= p[mid])
        {
            tree.update(a[j].l, a[j].r, a[j].v);
            a1[++cnta1] = a[j];
        }
        else
            a2[++cnta2] = a[j];

    for (int i = 1; i <= cnta1; ++i)
        tree.update(a1[i].l, a1[i].r, -a1[i].v);

    for (int i = 1; i <= cnta1; ++i)
        a[cl + i - 1] = a1[i];
    for (int i = 1; i <= cnta2; ++i)
        a[cr - cnta2 + i] = a2[i];

    for (int i = 1; i <= cntb1; ++i)
        b[ql + i - 1] = b1[i];
    for (int i = 1; i <= cntb2; ++i)
        b[qr - cntb2 + i] = b2[i];

    solve(cl, cl + cnta1 - 1, ql, ql + cntb1 - 1, l, mid);
    solve(cr - cnta2 + 1, cr, qr - cntb2 + 1, qr, mid + 1, r);
}
signed main()
{
    //	freopen("ans.in","r",stdin);
    //	freopen("ans.out","w",stdout);
    read(n, m, q);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    //	for(int i=1; i<=n; ++i)
    //		printf("%d %d\n",dfn[i].first,dfn[i].second);
    //	for(int i=1; i<=n; ++i)
    //		printf("%d ",dep[i]);
    //	putchar('\n');
    //	printf("%d\n",getlca(6,8));
    for (int i = 1; i <= m; ++i)
    {
        int x, y, v;
        read(x, y, v);
        p[++tot] = v;
        if (dfn[x] > dfn[y])
            swap(x, y);
        //		printf("%d %d %d\n",x,y,getlca(x,y));
        if (getlca(x, y) == x)
        {
            int z = jump(y, x);
            a[++cnt] = Matrix(1, dfn[y].first, dfn[y].second, v, 1);
            a[++cnt] = Matrix(dfn[z].first, dfn[y].first, dfn[y].second, v, -1);
            if (dfn[z].second < n)
            {
                a[++cnt] = Matrix(dfn[y].first, dfn[z].second + 1, n, v, 1);
                a[++cnt] = Matrix(dfn[y].second + 1, dfn[z].second + 1, n, v, -1);
            }
        }
        else
        {
            a[++cnt] = Matrix(dfn[x].first, dfn[y].first, dfn[y].second, v, 1);
            a[++cnt] = Matrix(dfn[x].second + 1, dfn[y].first, dfn[y].second, v, -1);
        }
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    for (int i = 1; i <= q; ++i)
    {
        b[i].id = i;
        int x, y;
        read(x, y, b[i].k);
        if (dfn[x].first > dfn[y].first)
            swap(x, y);
        b[i].x = dfn[x].first, b[i].y = dfn[y].first;
    }
    sort(a + 1, a + 1 + cnt);
    //	for(int i=1; i<=cnt; ++i)
    //		printf("%d %d %d %d %d\n",a[i].x,a[i].l,a[i].r,a[i].c,a[i].v);
    sort(b + 1, b + 1 + q);
    //	for(int i=1; i<=q; ++i)
    //		printf("%d %d %d\n",b[i].x,b[i].y,b[i].k);
    solve(1, cnt, 1, q, 1, tot);
    for (int i = 1; i <= q; ++i)
        printf("%d\n", p[answer[i]]);
    return 0;
}
