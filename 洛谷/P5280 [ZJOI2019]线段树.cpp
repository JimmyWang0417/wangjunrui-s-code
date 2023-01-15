/**
 *    unicode: UTF-8
 *    name:    P5280 [ZJOI2019]线段树
 *    author:  whitepaperdog
 *    created: 2022.07.24 周日 21:06:49 (Asia/Shanghai)
 **/
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
constexpr int N = 1e5 + 5;
constexpr int mod = 998244353;
int n, m;
struct Tree
{
    ll f, g;
    ll tagf, tagg;
    ll sum;
    inline void timesf(ll val)
    {
        (f *= val) %= mod;
        (tagf *= val) %= mod;
        (sum *= val) %= mod;
    }
    inline void timesg(ll val)
    {
        (g *= val) %= mod;
        (tagg *= val) %= mod;
    }
} tree[N * 8];
#define lc(rt) ((rt) << 1)
#define rc(rt) ((rt) << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].sum = (tree[rt].f + tree[lc(rt)].sum + tree[rc(rt)].sum) % mod;
}
inline void pushdown(int rt)
{
    if (tree[rt].tagf != 1)
    {
        tree[lc(rt)].timesf(tree[rt].tagf);
        tree[rc(rt)].timesf(tree[rt].tagf);
        tree[rt].tagf = 1;
    }
    if (tree[rt].tagg != 1)
    {
        tree[lc(rt)].timesg(tree[rt].tagg);
        tree[rc(rt)].timesg(tree[rt].tagg);
        tree[rt].tagg = 1;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].f = 0, tree[rt].g = 1;
    tree[rt].tagf = tree[rt].tagg = 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc(rt), l, mid);
    build(rc(rt), mid + 1, r);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    pushdown(rt);
    if (x <= l && r <= y)
    {
        (tree[rt].f += val) %= mod;
        if (l < r)
        {
            tree[lc(rt)].timesf(2);
            tree[rc(rt)].timesf(2);
        }
    }
    else
    {
        (tree[rt].g += val) %= mod;
        int mid = (l + r) >> 1;
        if (y <= mid)
        {
            update(lc(rt), l, mid, x, y, val);
            (tree[rc(rt)].f += val - tree[rc(rt)].g) %= mod;
            (tree[rc(rt)].g += tree[rc(rt)].g) %= mod;
            if (mid + 1 < r)
            {
                pushdown(rc(rt));
                tree[lc(rc(rt))].timesf(2), tree[lc(rc(rt))].timesg(2);
                tree[rc(rc(rt))].timesf(2), tree[rc(rc(rt))].timesg(2);
            }
            pushup(rc(rt));
        }
        else if (x > mid)
        {
            update(rc(rt), mid + 1, r, x, y, val);
            (tree[lc(rt)].f += val - tree[lc(rt)].g) %= mod;
            (tree[lc(rt)].g += tree[lc(rt)].g) %= mod;
            if (l < mid)
            {
                pushdown(lc(rt));
                tree[lc(lc(rt))].timesf(2), tree[lc(lc(rt))].timesg(2);
                tree[rc(lc(rt))].timesf(2), tree[rc(lc(rt))].timesg(2);
            }
            pushup(lc(rt));
        }
        else
        {
            update(lc(rt), l, mid, x, y, val);
            update(rc(rt), mid + 1, r, x, y, val);
        }
    }
    pushup(rt);
}
signed main()
{
    read(n, m);
    build(1, 1, n);
    for (int i = 1, j = 1; i <= m; ++i)
    {
        int opt, l, r;
        read(opt);
        if (opt == 1)
        {
            read(l, r);
            update(1, 1, n, l, r, j);
            (j += j) %= mod;
        }
        else
            printf("%lld\n", (tree[1].sum + mod) % mod);
    }
    return 0;
}