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
const int N = 3e5 + 10;
const int mod = 1e9 + 9;
int n, m, a[N];
int f[N];
struct Tree
{
    ll f1, f2, sum;
    int size;
    inline void update(ll _f1, ll _f2)
    {
        (sum += _f1 * f[size] + _f2 * (f[size + 1] - 1)) %= mod;
        (f1 += _f1) %= mod;
        (f2 += _f2) %= mod;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].sum = (tree[lc].sum + tree[rc].sum) % mod;
}
inline void pushdown(int rt)
{
    if (tree[rt].f1 || tree[rt].f2)
    {
        tree[lc].update(tree[rt].f1, tree[rt].f2);
        tree[rc].update((tree[rt].f1 * f[tree[lc].size - 1] + tree[rt].f2 * f[tree[lc].size]) % mod, (tree[rt].f1 * f[tree[lc].size] + tree[rt].f2 * f[tree[lc].size + 1]) % mod);
        tree[rt].f1 = tree[rt].f2 = 0;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].size = r - l + 1;
    if (l == r)
    {
        tree[rt].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(f[l - x + 1], f[l - x + 2]);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y);
    update(rc, mid + 1, r, x, y);
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
    return (query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y)) % mod;
}
signed main()
{
    read(n, m);
    f[1] = f[2] = 1;
    for (int i = 3; i <= n + 1; ++i)
        f[i] = (f[i - 1] + f[i - 2]) % mod;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, l, r;
        read(opt, l, r);
        if (opt == 1)
            update(1, 1, n, l, r);
        else
            printf("%lld\n", query(1, 1, n, l, r));
    }
    return 0;
}