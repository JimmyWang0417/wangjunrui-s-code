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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 5e5 + 5;
int n, m;
struct Tree
{
    ll lmin, rmin, min;
    ll lmax, rmax, max;
    ll sum;
    inline void init(int val)
    {
        lmin = rmin = min = lmax = rmax = max = sum = val;
    }
} tree[N * 4];
#define lc(rt) (rt << 1)
#define rc(rt) (rt << 1 | 1)
int a[N];
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc(rt)].sum + tree[rc(rt)].sum;
    tree[rt].lmin = min(tree[lc(rt)].lmin, tree[lc(rt)].sum + tree[rc(rt)].lmin);
    tree[rt].rmin = min(tree[lc(rt)].rmin + tree[rc(rt)].sum, tree[rc(rt)].rmin);
    tree[rt].min = min(min(tree[lc(rt)].min, tree[rc(rt)].min), tree[lc(rt)].rmin + tree[rc(rt)].lmin);
    tree[rt].lmax = max(tree[lc(rt)].lmax, tree[lc(rt)].sum + tree[rc(rt)].lmax);
    tree[rt].rmax = max(tree[lc(rt)].rmax + tree[rc(rt)].sum, tree[rc(rt)].rmax);
    tree[rt].max = max(max(tree[lc(rt)].max, tree[rc(rt)].max), tree[lc(rt)].rmax + tree[rc(rt)].lmax);
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].init((l & 1) ? a[l] : -a[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(rt), l, mid);
    build(rc(rt), mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].init((l & 1) ? val : -val);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos, val);
    else
        update(rc(rt), mid + 1, r, pos, val);
    pushup(rt);
}
int S;
inline ll solve(int rt, int l, int r, int val)
{
    if (l == r)
        return max(0ll, min((ll)S, val + tree[rt].sum));
    int mid = (l + r) >> 1;
    if (tree[rc(rt)].max > S || tree[rc(rt)].min < -S)
        return solve(rc(rt), mid + 1, r, val);
    ll res = solve(lc(rt), l, mid, val);
    if (res + tree[rc(rt)].lmax > S)
        return S + tree[rc(rt)].sum - tree[rc(rt)].lmax;
    if (res + tree[rc(rt)].lmin < 0)
        return tree[rc(rt)].sum - tree[rc(rt)].lmin;
    return res + tree[rc(rt)].sum;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("sheepandcow.in", "r", stdin);
    freopen("sheepandcow.out", "w", stdout);
#endif
    int x, y;
    read(n, m, x, y);
    S = x + y;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, u, v;
        read(opt);
        if (opt == 1)
        {
            read(x);
            S = x + y;
        }
        else if (opt == 2)
        {
            read(y);
            S = x + y;
        }
        else
        {
            read(u, v);
            update(1, 1, n, u, v);
        }
        printf("%lld\n", solve(1, 1, n, x));
    }
    return 0;
}
