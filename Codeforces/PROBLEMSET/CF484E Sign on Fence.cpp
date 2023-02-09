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
int n, m, a[N];
int p[N], tot;
struct node
{

    int pre, suf, ans, size;
    node(int _pre = 0, int _suf = 0, int _ans = 0, int _size = 0) : pre(_pre), suf(_suf), ans(_ans), size(_size) {}
    inline node operator+(const node &rhs) const
    {
        node res;
        res.ans = max(max(ans, rhs.ans), suf + rhs.pre);
        res.pre = (pre == size ? pre + rhs.pre : pre);
        res.suf = (rhs.suf == rhs.size ? suf + rhs.suf : rhs.suf);
        res.size = size + rhs.size;
        return res;
    }
};
struct Tree
{
    node ans;
    int l, r;
} tree[N * 50];
#define lc(rt) (tree[rt].l)
#define rc(rt) (tree[rt].r)
int root[N], cnt;
inline void pushup(int rt)
{
    tree[rt].ans = tree[lc(rt)].ans + tree[rc(rt)].ans;
}
inline void build(int &rt, int l, int r)
{
    rt = ++cnt;
    if (l == r)
    {
        tree[rt].ans = node(0, 0, 0, 1);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(rt), l, mid);
    build(rc(rt), mid + 1, r);
    pushup(rt);
}
inline void update(int pre, int &rt, int l, int r, int pos)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    if (l == r)
    {
        tree[rt].ans = node(1, 1, 1, 1);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos);
    pushup(rt);
}
inline node query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt].ans;
    int mid = (l + r) >> 1;
    if (y <= mid)
        return query(lc(rt), l, mid, x, y);
    if (x > mid)
        return query(rc(rt), mid + 1, r, x, y);
    return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
}
list<int> g[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[i] = a[i];
    }
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
        g[a[i]].push_back(i);
    }
    build(root[tot + 1], 1, n);
    for (int i = tot; i >= 1; --i)
    {
        root[i] = root[i + 1];
        for (auto u : g[i])
            update(root[i], root[i], 1, n, u);
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y, k;
        read(x, y, k);
        int l = 1, r = tot, ans = tot + 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (query(root[mid], 1, n, x, y).ans >= k)
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("%d\n", p[ans]);
    }
    return 0;
}