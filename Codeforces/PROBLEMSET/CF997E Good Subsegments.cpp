// Problem: E. Good Subsegments
// Contest: Codeforces - Codeforces Round #493 (Div. 1)
// URL: https://codeforces.com/problemset/problem/997/E
// Memory Limit: 512 MB
// Time Limit: 7000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
constexpr int N = 1.2e5 + 5;
int n, m;
int mp[N], a[N];
struct Tree
{
    int min, cnt;
    int tag;
    int anstag;
    ll ans;
    inline void update(int val)
    {
        tag += val;
        min += val;
    }
    inline void add(int val)
    {
        ans += (ll)val * cnt;
        anstag += val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].ans = tree[lc].ans + tree[rc].ans;

    tree[rt].min = min(tree[lc].min, tree[rc].min);
    tree[rt].cnt = 0;
    if (tree[rt].min == tree[lc].min)
        tree[rt].cnt += tree[lc].cnt;
    if (tree[rt].min == tree[rc].min)
        tree[rt].cnt += tree[rc].cnt;
}
inline void pushdown(int rt)
{
    if (tree[rt].tag)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
    }
    if (tree[rt].anstag)
    {
        if (tree[rt].min == tree[lc].min)
            tree[lc].add(tree[rt].anstag);
        if (tree[rt].min == tree[rc].min)
            tree[rc].add(tree[rt].anstag);
        tree[rt].anstag = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].cnt = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (x <= l && r <= y)
    {
        tree[rt].update(val);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (y <= mid)
        update(lc, l, mid, x, y, val);
    else if (mid < x)
        update(rc, mid + 1, r, x, y, val);
    else
    {
        update(lc, l, mid, x, y, val);
        update(rc, mid + 1, r, x, y, val);
    }
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y)
{
    if (tree[rt].min > 1)
        return;
    if (x <= l && r <= y)
    {
        tree[rt].add(1);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (y <= mid)
        update(lc, l, mid, x, y);
    else if (mid < x)
        update(rc, mid + 1, r, x, y);
    else
    {
        update(lc, l, mid, x, y);
        update(rc, mid + 1, r, x, y);
    }
    pushup(rt);
}
inline void dfs1(int rt, int l, int r)
{
    if (l == r)
    {
        printf("%d ", tree[rt].min);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    dfs1(lc, l, mid);
    dfs1(rc, mid + 1, r);
    pushup(rt);
}
inline void dfs2(int rt, int l, int r)
{
    if (l == r)
    {
        printf("%lld ", tree[rt].ans);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    dfs2(lc, l, mid);
    dfs2(rc, mid + 1, r);
    pushup(rt);
}
inline int querymin(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt].min;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (y <= mid)
        return querymin(lc, l, mid, x, y);
    else if (mid < x)
        return querymin(rc, mid + 1, r, x, y);
    else
        return min(querymin(lc, l, mid, x, y), querymin(rc, mid + 1, r, x, y));
}
inline ll querysum(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt].ans;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (y <= mid)
        return querysum(lc, l, mid, x, y);
    else if (mid < x)
        return querysum(rc, mid + 1, r, x, y);
    else
        return querysum(lc, l, mid, x, y) + querysum(rc, mid + 1, r, x, y);
}
struct node
{
    int l, r, id;
    inline bool operator<(const node &rhs) const
    {
        return r < rhs.r;
    }
} b[N];
ll answer[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        mp[a[i]] = i;
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        read(b[i].l, b[i].r);
        b[i].id = i;
    }
    sort(b + 1, b + 1 + m);
    build(1, 1, n);
    for (int i = 1, r = 1; i <= m; ++i)
    {
        while (r <= b[i].r)
        {
            update(1, 1, n, 1, r, 1);
            if (a[r] > 1 && mp[a[r] - 1] <= r)
                update(1, 1, n, 1, mp[a[r] - 1], -1);
            if (a[r] < n && mp[a[r] + 1] <= r)
                update(1, 1, n, 1, mp[a[r] + 1], -1);
            update(1, 1, n, 1, r);
            ++r;
        }
        answer[b[i].id] = querysum(1, 1, n, b[i].l, b[i].r);
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}