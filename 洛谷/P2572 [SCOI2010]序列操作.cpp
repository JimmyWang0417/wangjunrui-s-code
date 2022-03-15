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
struct node
{
    int size, pre, suf, ans;
    node(int _size = 0, int _pre = 0, int _suf = 0, int _ans = 0) : size(_size), pre(_pre), suf(_suf), ans(_ans) {}
    inline node friend operator+(const node &lhs, const node &rhs)
    {
        node res;
        res.size = lhs.size + rhs.size;
        if (lhs.pre && lhs.pre == lhs.size && lhs.suf == lhs.size)
            res.pre = lhs.size + rhs.pre;
        else
            res.pre = lhs.pre;
        if (rhs.suf && rhs.suf == rhs.size && rhs.pre == rhs.size)
            res.suf = lhs.suf + rhs.size;
        else
            res.suf = rhs.suf;
        res.ans = max(max(lhs.ans, rhs.ans), lhs.suf + rhs.pre);
        return res;
    }
};
struct Tree
{
    node ans[2];
    int size;
    int tag;
    bool rev;
    inline void update(int val)
    {
        tag = val;
        ans[val] = node(size, size, size, size);
        ans[val ^ 1] = node();
    }
    inline void reverse()
    {
        swap(ans[0], ans[1]);
        if (tag != -1)
            tag ^= 1;
        rev ^= 1;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
int n, m, a[N];
inline void pushup(int rt)
{
    tree[rt].ans[0] = tree[lc].ans[0] + tree[rc].ans[0];
    tree[rt].ans[1] = tree[lc].ans[1] + tree[rc].ans[1];
}
inline void pushdown(int rt)
{
    if (tree[rt].rev)
    {
        tree[lc].reverse();
        tree[rc].reverse();
        tree[rt].rev = false;
    }
    if (tree[rt].tag != -1)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = -1;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].tag = -1;
    tree[rt].size = r - l + 1;
    if (l == r)
    {
        tree[rt].update(a[l]);
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
    if (x <= l && r <= y)
        return tree[rt].update(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline void reverse(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].reverse();
    int mid = (l + r) >> 1;
    pushdown(rt);
    reverse(lc, l, mid, x, y);
    reverse(rc, mid + 1, r, x, y);
    pushup(rt);
}
inline node query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return node();
    if (x <= l && r <= y)
        return tree[rt].ans[1];
    int mid = (l + r) >> 1;
    pushdown(rt);
    // if (y <= mid)
    //     return query(lc, l, mid, x, y);
    // if (mid < x)
    //     return query(rc, mid + 1, r, x, y);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, l, r;
        read(opt, l, r);
        ++l, ++r;
        if (opt == 0)
            update(1, 1, n, l, r, 0);
        else if (opt == 1)
            update(1, 1, n, l, r, 1);
        else if (opt == 2)
            reverse(1, 1, n, l, r);
        else if (opt == 3)
            printf("%d\n", query(1, 1, n, l, r).size);
        else
            printf("%d\n", query(1, 1, n, l, r).ans);
    }
    return 0;
}