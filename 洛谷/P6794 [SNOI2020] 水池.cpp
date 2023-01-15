/**
 *    unicode: UTF-8
 *    name:    P6794 [SNOI2020] 水池
 *    author:  whitepaperdog
 *    created: 2022.08.15 周一 09:29:05 (Asia/Shanghai)
 **/
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
constexpr int N = 2e5 + 5;
constexpr int M = 2e7 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, m;
int a[N];
struct Tree
{
    int l, r;
    int tag;
    int pre, suf;
    int h, mid;
    inline void assign(int val)
    {
        tag = val;
        pre = suf = INF;
    }
} tree[M];
#define lc(rt) (tree[rt].l)
#define rc(rt) (tree[rt].r)
int root[N], tot;
inline int newnode(int rt)
{
    tree[++tot] = tree[rt];
    return tot;
}
inline void pushup(int rt)
{
    tree[rt].h = max(tree[rt].mid,
                     max(tree[lc(rt)].h, tree[rc(rt)].h));
}
inline void pushdown(int rt)
{
    lc(rt) = newnode(lc(rt)), rc(rt) = newnode(rc(rt));
    if (tree[rt].tag)
    {
        tree[lc(rt)].assign(tree[rt].tag);
        tree[rc(rt)].assign(tree[rt].tag);
        tree[rt].tag = 0;
    }
    if (tree[rt].pre < INF)
    {
        ckmin(tree[lc(rt)].pre, tree[rt].pre);
        ckmin(tree[rc(rt)].pre, max(tree[rt].pre, max(tree[rt].mid, tree[lc(rt)].h)));
        tree[rt].pre = INF;
    }
    if (tree[rt].suf < INF)
    {
        ckmin(tree[lc(rt)].suf, max(tree[rt].suf, max(tree[rt].mid, tree[rc(rt)].h)));
        ckmin(tree[rc(rt)].suf, tree[rt].suf);
        tree[rt].suf = INF;
    }
}
inline void build(int &rt, int l, int r)
{
    rt = ++tot;
    if (l == r)
    {
        tree[rt].pre = tree[rt].suf = INF;
        return;
    }
    int mid = (l + r) >> 1;
    tree[rt].mid = a[mid];
    build(lc(rt), l, mid);
    build(rc(rt), mid + 1, r);
    pushup(rt);
}
inline int queryl(int rt, int l, int r, int pos, int val)
{
    if (r <= pos && tree[rt].h < val)
        return l;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return queryl(lc(rt), l, mid, pos, val);
    int res = queryl(rc(rt), mid + 1, r, pos, val);
    if (res == mid + 1 && tree[rt].mid < val)
        res = queryl(lc(rt), l, mid, pos, val);
    return res;
}
inline int queryr(int rt, int l, int r, int pos, int val)
{
    if (l >= pos && tree[rt].h < val)
        return r;
    int mid = (l + r) >> 1;
    if (pos > mid)
        return queryr(rc(rt), mid + 1, r, pos, val);
    int res = queryr(lc(rt), l, mid, pos, val);
    if (res == mid && tree[rt].mid < val)
        res = queryr(rc(rt), mid + 1, r, pos, val);
    return res;
}
inline int updatel(int rt, int l, int r, int pos, int val)
{
    if (r <= pos)
    {
        ckmin(tree[rt].suf, val);
        return max(tree[rt].h, val);
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        return updatel(lc(rt), l, mid, pos, val);
    else
        return updatel(lc(rt), l, mid, pos, max(tree[rt].mid, updatel(rc(rt), mid + 1, r, pos, val)));
}
inline int updater(int rt, int l, int r, int pos, int val)
{
    if (l >= pos)
    {
        ckmin(tree[rt].pre, val);
        return max(tree[rt].h, val);
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        return updater(rc(rt), mid + 1, r, pos, max(tree[rt].mid, updater(lc(rt), l, mid, pos, val)));
    else
        return updater(rc(rt), mid + 1, r, pos, val);
}
inline void assign(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].assign(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    assign(lc(rt), l, mid, x, y, val);
    assign(rc(rt), mid + 1, r, x, y, val);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        a[l] = val;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos < r)
        ckmax(tree[rt].h, val);
    if (mid == pos)
        tree[rt].mid = val;
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val);
    else
        update(rc(rt), mid + 1, r, pos, val);
    pushup(rt);
}
inline int query(int rt, int l, int r, int pos)
{
    if (l == r)
        return min(tree[rt].tag, min(tree[rt].pre, tree[rt].suf));
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        return query(lc(rt), l, mid, pos);
    else
        return query(rc(rt), mid + 1, r, pos);
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n, m);
    a[0] = a[n] = INF;
    for (int i = 1; i < n; ++i)
        read(a[i]);
    build(root[0], 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, las, x, y;
        read(opt, las, x);
        root[i] = newnode(root[las]);
        if (opt == 0)
        {
            read(y);
            if (query(root[i], 1, n, x) < y)
            {
                int l = queryl(root[i], 1, n, x, y),
                    r = queryr(root[i], 1, n, x, y);
                assign(root[i], 1, n, l, r, y);
            }
        }
        else if (opt == 1)
        {
            updatel(root[i], 1, n, x, 0);
            updater(root[i], 1, n, x, 0);
        }
        else if (opt == 2)
        {
            read(y);
            update(root[i], 1, n, x, y);
        }
        else
            printf("%d\n", query(root[i], 1, n, x));
    }
    return 0;
}