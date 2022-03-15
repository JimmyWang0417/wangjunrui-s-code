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
using namespace std;
const int N = 1.1e6 + 5;
struct Point
{
    int ch[26], fa, len;
} point[N];
int las = 1, tot = 1;
inline int insert(int c)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
    return np;
}
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
struct node
{
    int id, ans;
    node(int _id = 0, int _ans = 0) : id(_id), ans(_ans) {}
    inline node operator+(const node &rhs) const
    {
        return ans < rhs.ans ? rhs : (*this);
    }
};
struct Tree
{
    int l, r;
    node size;
} tree[N * 10];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline void pushup(int rt)
{
    tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size;
}
inline void update(int &rt, int l, int r, int pos)
{
    rt = ++cnt;
    if (l == r)
    {
        tree[rt].size = node(l, 1);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos);
    else
        update(rc(rt), mid + 1, r, pos);
    pushup(rt);
}
inline int merge(int x, int y, int l, int r)
{
    if (!x || !y)
        return x | y;
    int rt = ++cnt;
    if (l == r)
    {
        tree[rt].size = node(l, tree[x].size.ans + tree[y].size.ans);
        return rt;
    }
    int mid = (l + r) >> 1;
    lc(rt) = merge(lc(x), lc(y), l, mid);
    rc(rt) = merge(rc(x), rc(y), mid + 1, r);
    pushup(rt);
    return rt;
}
inline node query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return node();
    if (x <= l && r <= y)
        return tree[rt].size;
    int mid = (l + r) >> 1;
    return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
}
int n, m;
int id[N];
char str[N];
int fa[N][25];
inline void dfs(int u)
{
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        fa[v][0] = u;
        dfs(v);
        root[u] = merge(root[u], root[v], 1, n);
    }
}
inline int getroot(int u, int len)
{
    for (int i = 20; i >= 0; --i)
        if (point[fa[u][i]].len >= len)
            u = fa[u][i];
    return u;
}
inline void dfs(int rt, int l, int r)
{
    if (l == r)
    {
        printf("%d ", tree[rt].size.ans);
        return;
    }
    int mid = (l + r) >> 1;
    dfs(lc(rt), l, mid);
    dfs(rc(rt), mid + 1, r);
    pushup(rt);
}
inline void print(int rt)
{
    dfs(rt, 1, n);
    putchar('\n');
}
signed main()
{
    scanf("%s", str + 1);
    for (int i = 1; str[i]; ++i)
        id[i] = insert(str[i] - 'a');
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str + 1);
        las = 1;
        for (int j = 1; str[j]; ++j)
            update(root[insert(str[j] - 'a')], 1, n, i);
    }
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y, l, r;
        read(x, y, l, r);
        node res = query(root[getroot(id[r], r - l + 1)], 1, n, x, y);
        printf("%d %d\n", !res.ans ? x : res.id, res.ans);
    }
    return 0;
}