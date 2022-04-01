#include <algorithm>
#include <cstdio>
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
constexpr int N = 1e5 + 5, M = 25;
int n, m, q, p[N];
struct node
{
    int a[M];
    template <typename T>
    inline int &operator[](const T &x)
    {
        return a[x];
    }
} tree[N * 4], a[N];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    for (int i = 1; i <= m; ++i)
        tree[rt][i] = max(tree[lc][i], tree[rc][i]);
}
inline void build(int rt, int l, int r)
{
    for (int i = 1; i <= m; ++i)
        tree[rt][i] = ~0x7fffffff;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int pos)
{
    if (l == r)
    {
        tree[rt][p[pos]] = a[pos][p[pos]];
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos);
    else
        update(rc, mid + 1, r, pos);
    pushup(rt);
}
inline int query(int rt, int l, int r, int pos)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    for (int i = 1; i <= m; ++i)
        if (tree[lc][i] > a[pos][i])
            return query(lc, l, mid, pos);
    return query(rc, mid + 1, r, pos);
}
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
signed main()
{
    freopen("gift.in", "r", stdin);
    freopen("gift.out", "w", stdout);
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(p[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            read(a[i][j]);
    build(1, 1, n);
    for (int i = n; i >= 1; --i)
    {
        for (int j = 1; j <= m; ++j)
            if (tree[1][j] > a[i][j])
            {
                fa[i] = query(1, 1, n, i);
                break;
            }
        update(1, 1, n, i);
        continue;
    }
    read(q);
    while (q--)
    {
        bool flag = true;
        for (int i = 1; i <= m; ++i)
            read(a[0][i]);
        for (int i = 1; i <= m; ++i)
            if (tree[1][i] > a[0][i])
            {
                printf("%d\n", find(query(1, 1, n, 0)));
                flag = false;
                break;
            }
        if (flag)
            printf("0\n");
    }
    return 0;
}
