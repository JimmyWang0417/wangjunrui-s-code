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
const int N = 1e5 + 5;
#define calc(x) ((ll)x * (x + 1) * (x + 2) / 6)
int n, m;
struct Tree
{
    int tag;
    ll sum1, sum2, sum3;
    ll size1, size2, size3;
    inline void update(int val)
    {
        tag += val;
        sum1 += size1 * val;
        sum2 += size2 * val;
        sum3 += size3 * val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushdown(int rt)
{
    if (tree[rt].tag)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].size1 = 1;
        tree[rt].size2 = l;
        tree[rt].size3 = (ll)l * l;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[rt].size1 = tree[lc].size1 + tree[rc].size1;
    tree[rt].size2 = tree[lc].size2 + tree[rc].size2;
    tree[rt].size3 = tree[lc].size3 + tree[rc].size3;
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    tree[rt].sum1 = tree[lc].sum1 + tree[rc].sum1;
    tree[rt].sum2 = tree[lc].sum2 + tree[rc].sum2;
    tree[rt].sum3 = tree[lc].sum3 + tree[rc].sum3;
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum1 * (y + 1) * (1 - x) + tree[rt].sum2 * (x + y) - tree[rt].sum3;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
signed main()
{
    read(n, m);
    --n;
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        char opt[4];
        scanf("%s", opt);
        int l, r;
        read(l, r);
        --r;
        if (opt[0] == 'C')
        {
            int c;
            read(c);
            update(1, 1, n, l, r, c);
        }
        else
        {
            ll a = query(1, 1, n, l, r), b = (ll)(r - l + 1) * (r - l + 2) / 2, g = __gcd(a, b);
            a /= g, b /= g;
            printf("%lld/%lld\n", a, b);
        }
    }
    return 0;
}