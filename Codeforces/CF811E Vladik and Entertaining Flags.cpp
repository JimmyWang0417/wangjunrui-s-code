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
constexpr int N = 1e5 + 5, M = 15;
int n, m, q;
int a[M][N];
int fa[M * N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
struct Tree
{
    int l[M], r[M];
    int size;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline int calc(int x, int y)
{
    return (x - 1) * m + y;
}
inline Tree merge(Tree lhs, Tree rhs, int mid)
{
    for (int i = 1; i <= n; ++i)
        fa[lhs.l[i]] = fa[lhs.r[i]] = fa[rhs.l[i]] = fa[rhs.r[i]] = 0;
    Tree res;
    res.size = lhs.size + rhs.size;
    for (int i = 1; i <= n; ++i)
        if (a[i][mid] == a[i][mid + 1])
        {
            if (find(lhs.r[i]) != find(rhs.l[i]))
            {
                --res.size;
                fa[find(lhs.r[i])] = find(rhs.l[i]);
            }
        }
    for (int i = 1; i <= n; ++i)
    {
        res.l[i] = find(lhs.l[i]);
        res.r[i] = find(rhs.r[i]);
    }
    return res;
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        for (int i = 1; i <= n; ++i)
            if (a[i][l] == a[i + 1][l])
                fa[calc(i, l)] = calc(i + 1, l);
            else
                ++tree[rt].size;
        for (int i = 1; i <= n; ++i)
            tree[rt].l[i] = tree[rt].r[i] = find(calc(i, l));
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[rt] = merge(tree[lc], tree[rc], mid);
}
inline Tree query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    if (y <= mid)
        return query(lc, l, mid, x, y);
    if (x > mid)
        return query(rc, mid + 1, r, x, y);
    return merge(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y), mid);
}
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            read(a[i][j]);
    build(1, 1, m);
    for (int i = 1; i <= q; ++i)
    {
        int l, r;
        read(l, r);
        printf("%d\n", query(1, 1, m, l, r).size);
    }
    return 0;
}