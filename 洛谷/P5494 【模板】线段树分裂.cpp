#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 2e5 + 5;
int n, m;
struct Tree
{
    int l, r;
    ll size;
} tree[N * 40];
int recyclenum[N], recyclecnt;
int root[N], rootcnt = 1, cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline int newnode()
{
    return recyclecnt ? recyclenum[recyclecnt--] : ++cnt;
}
inline void recycle(int x)
{
    recyclenum[++recyclecnt] = x;
    tree[x].size = lc(x) = rc(x) = 0;
}
inline void pushup(int rt)
{
    tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size;
}
inline void build(int &rt, int l, int r)
{
    rt = newnode();
    if (l == r)
    {
        read(tree[rt].size);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(rt), l, mid);
    build(rc(rt), mid + 1, r);
    pushup(rt);
}
inline void update(int &rt, int l, int r, int pos, int val)
{
    if (!rt)
        rt = newnode();
    tree[rt].size += val;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val);
    else
        update(rc(rt), mid + 1, r, pos, val);
}
inline void split(int &pre, int &rt, int l, int r, int x, int y)
{
    if (!pre || r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        rt = pre;
        pre = 0;
        return;
    }
    if (!rt)
        rt = newnode();
    int mid = (l + r) >> 1;
    split(lc(pre), lc(rt), l, mid, x, y);
    split(rc(pre), rc(rt), mid + 1, r, x, y);
    pushup(pre);
    pushup(rt);
}
inline void merge(int &x, int &y, int l, int r)
{
    if (!x || !y)
    {
        x = x | y;
        return;
    }
    if (l == r)
    {
        tree[x].size += tree[y].size;
        recycle(y);
        return;
    }
    int mid = (l + r) >> 1;
    tree[x].size += tree[y].size;
    merge(lc(x), lc(y), l, mid);
    merge(rc(x), rc(y), mid + 1, r);
    recycle(y);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].size;
    int mid = (l + r) >> 1;
    return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
}
inline int query(int rt, int l, int r, ll k_th)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (k_th <= tree[lc(rt)].size)
        return query(lc(rt), l, mid, k_th);
    else
        return query(rc(rt), mid + 1, r, k_th - tree[lc(rt)].size);
}
signed main()
{
    read(n, m);
    build(root[1], 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, p;
        read(opt, p);
        if (opt == 0)
        {
            int x, y;
            read(x, y);
            split(root[p], root[++rootcnt], 1, n, x, y);
        }
        else if (opt == 1)
        {
            int x;
            read(x);
            merge(root[p], root[x], 1, n);
        }
        else if (opt == 2)
        {
            int x, y;
            read(x, y);
            update(root[p], 1, n, y, x);
        }
        else if (opt == 3)
        {
            int x, y;
            read(x, y);
            printf("%lld\n", query(root[p], 1, n, x, y));
        }
        else
        {
            ll k;
            read(k);
            if (tree[root[p]].size < k)
                printf("-1\n");
            else
                printf("%d\n", query(root[p], 1, n, k));
        }
    }
    return 0;
}