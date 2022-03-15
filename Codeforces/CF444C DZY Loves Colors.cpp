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
const int N = 1e5 + 5;
int n, m;
struct Tree
{
    int size;
    int color;
    ll tag, sum;
    inline void update(ll val)
    {
        tag += val;
        sum += val * size;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    if (tree[lc].color == tree[rc].color)
        tree[rt].color = tree[lc].color;
    else
        tree[rt].color = 0;
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
}
inline void pushdown(int rt)
{
    if (tree[rt].color)
    {
        tree[lc].color = tree[rt].color;
        tree[lc].update(tree[rt].tag);
        tree[rc].color = tree[rt].color;
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].size = r - l + 1;
    if (l == r)
    {
        tree[rt].color = l;
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
    if (tree[rt].color && x <= l && r <= y)
    {
        tree[rt].update(abs(val - tree[rt].color));
        tree[rt].color = val;
        return;
    }
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
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
signed main()
{
    read(n, m);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, l, r, x;
        read(opt, l, r);
        if (opt == 1)
        {
            read(x);
            update(1, 1, n, l, r, x);
        }
        else
            printf("%lld\n", query(1, 1, n, l, r));
    }
    return 0;
}