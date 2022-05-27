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
constexpr int N = 5e4 + 5, M = N * 8;
inline ll f(ll a, ll b, ll c, ll n)
{
    ll ac = a / c, bc = b / c, m = (a * n + b) / c;
    if (a == 0)
        return bc * (m + 1);
    else if (a >= c || b >= c)
        return n * (n + 1) / 2 * ac + (n + 1) * bc + f(a % c, b % c, c, n);
    return n * m - f(c, c - b - 1, a, m - 1);
}
struct Tree
{
    int size;
    ll sum;
    ll add;
    int A, B;
    inline void update(int _A, int _B, ll _add)
    {
        A = _A, B = _B, add = _add;
        sum = (ll)size * (size - 1) / 2 * A + add * size - (ll)B * f(A, add, B, size - 1);
    }
} tree[M];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
int cnt, root;
int p[N * 2], tot;
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
}
inline void pushdown(int rt)
{
    if (tree[rt].A)
    {
        tree[lc].update(tree[rt].A, tree[rt].B, tree[rt].add);
        tree[rc].update(tree[rt].A, tree[rt].B, tree[rt].add + (ll)tree[lc].size * tree[rt].A);
        tree[rt].A = 0;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].size = p[r] - p[l - 1];
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int x, int y, int A, int B)
{
    if (p[r] < x || p[l - 1] >= y)
        return;
    if (x <= p[l - 1] + 1 && p[r] <= y)
        return tree[rt].update(A, B, (ll)(p[l - 1] - x + 2) * A);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, A, B);
    update(rc, mid + 1, r, x, y, A, B);
    pushup(rt);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (p[r] < x || p[l - 1] >= y)
        return 0;
    if (x <= p[l - 1] + 1 && p[r] <= y)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
struct Query
{
    int opt, l, r, a, b;
} q[N];
int n, m;
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int &opt = q[i].opt, &l = q[i].l, &r = q[i].r, &a = q[i].a, &b = q[i].b;
        read(opt);
        if (opt == 1)
            read(l, r, a, b);
        else
            read(l, r);
        p[++tot] = q[i].l - 1;
        p[++tot] = q[i].r;
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    build(1, 1, tot);
    for (int i = 1; i <= m; ++i)
    {
        int &opt = q[i].opt, &l = q[i].l, &r = q[i].r, &a = q[i].a, &b = q[i].b;
        if (opt == 1)
            update(1, 1, tot, l, r, a, b);
        else
            printf("%lld\n", query(1, 1, tot, l, r));
    }
    return 0;
}