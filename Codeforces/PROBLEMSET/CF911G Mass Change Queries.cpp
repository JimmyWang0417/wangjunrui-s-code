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
const int N = 2e5 + 5;
int n, m, a[N];
struct Tree
{
    int l, r;
} tree[N * 100];
int root[N], cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void update(int &rt, int l, int r, int pos)
{
    if (!rt)
        rt = ++cnt;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(rt), l, mid, pos);
    else
        update(rc(rt), mid + 1, r, pos);
}
inline void split(int &pre, int &rt, int l, int r, int x, int y)
{
    if (!pre || r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        rt = pre;
        pre = 0;
        return;
    }
    if (!rt)
        rt = ++cnt;
    int mid = (l + r) >> 1;
    split(lc(pre), lc(rt), l, mid, x, y);
    split(rc(pre), rc(rt), mid + 1, r, x, y);
}
inline void merge(int &x, int &y, int l, int r)
{
    if (!x || !y)
    {
        x = x | y;
        return;
    }
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    merge(lc(x), lc(y), l, mid);
    merge(rc(x), rc(y), mid + 1, r);
}
inline void solve(int &rt, int l, int r, int val)
{
    if (!rt)
        return;
    if (l == r)
    {
        a[l] = val;
        return;
    }
    int mid = (l + r) >> 1;
    solve(lc(rt), l, mid, val);
    solve(rc(rt), mid + 1, r, val);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        update(root[x], 1, n, i);
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r, x, y;
        read(l, r, x, y);
        int rt = 0;
        split(root[x], rt, 1, n, l, r);
        merge(root[y], rt, 1, n);
    }
    for (int i = 1; i <= 100; ++i)
        solve(root[i], 1, n, i);
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
    putchar('\n');
    return 0;
}