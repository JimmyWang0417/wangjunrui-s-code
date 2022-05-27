// Problem: C. Alyona and towers
// Contest: Codeforces - Codeforces Round #381 (Div. 1)
// URL: https://codeforces.com/problemset/problem/739/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
const int N = 3e5 + 5;
int n, m, a[N];
struct Tree
{
    int size;
    int pre, suf, ans;
    ll lcolor, rcolor;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].ans = max(tree[lc].ans, tree[rc].ans);
    tree[rt].lcolor = tree[lc].lcolor, tree[rt].rcolor = tree[rc].rcolor;
    if (!tree[lc].rcolor || !tree[rc].lcolor || (tree[lc].rcolor < 0 && tree[rc].lcolor > 0))
    {
        tree[rt].pre = tree[lc].pre;
        tree[rt].suf = tree[rc].suf;
    }
    else
    {
        ckmax(tree[rt].ans, tree[lc].suf + tree[rc].pre);
        tree[rt].pre = (tree[lc].pre == tree[lc].size ? tree[lc].pre + tree[rc].pre : tree[lc].pre);
        tree[rt].suf = (tree[rc].suf == tree[rc].size ? tree[lc].suf + tree[rc].suf : tree[rc].suf);
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].size = r - l + 1;
    if (l == r)
    {
        tree[rt].lcolor = tree[rt].rcolor = a[l + 1] - a[l];
        tree[rt].pre = tree[rt].suf = tree[rt].ans = (tree[rt].lcolor ? 1 : 0);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].lcolor += val, tree[rt].rcolor += val;
        tree[rt].pre = tree[rt].suf = tree[rt].ans = (tree[rt].lcolor ? 1 : 0);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    read(m);
    if (n == 1)
    {
        for (int i = 1; i <= m; ++i)
            printf("1\n");
        return 0;
    }
    --n;
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int l, r, d;
        read(l, r, d);
        if (l > 1)
            update(1, 1, n, l - 1, d);
        if (r <= n)
            update(1, 1, n, r, -d);
        printf("%d\n", tree[1].ans + 1);
    }
    return 0;
}