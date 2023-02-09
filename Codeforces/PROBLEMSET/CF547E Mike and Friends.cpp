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
constexpr int N = 4e5 + 5;
int n, m;
char str[N];
struct Point
{
    int ch[26], fa;
    int len;
} point[N];
int las = 1, tot = 1;
inline int insert(int c)
{
    int p = las;
    if (point[p].ch[c])
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            return las = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
            return las = nq;
        }
    }
    int np = las = ++tot;
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
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int dfn[N], low[N], dfstime;
inline void dfs(int u, int _fa)
{
    dfn[u] = ++dfstime;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
    low[u] = dfstime;
}
vector<int> g[N];
struct Tree
{
    int l, r;
    int size;
} tree[N * 40];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline void update(int &rt, int l, int r, int pos)
{
    tree[++cnt] = tree[rt];
    rt = cnt;
    ++tree[rt].size;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos);
    else
        update(rc(rt), mid + 1, r, pos);
}
inline int query(int rootl, int rootr, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rootr].size - tree[rootl].size;
    int mid = (l + r) >> 1;
    return query(lc(rootl), lc(rootr), l, mid, x, y) + query(rc(rootl), rc(rootr), mid + 1, r, x, y);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str);
        for (int j = 0; str[j]; ++j)
            g[i].push_back(insert(str[j] - 'a'));
        las = 1;
    }
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
    {
        root[i] = root[i - 1];
        for (auto u : g[i])
            update(root[i], 1, tot, dfn[u]);
    }
    for (int i = 1; i <= m; ++i)
    {
        int l, r, k;
        read(l, r, k);
        printf("%d\n", query(root[l - 1], root[r], 1, tot, dfn[g[k].back()], low[g[k].back()]));
    }
    return 0;
}