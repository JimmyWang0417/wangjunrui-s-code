#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e5 + 5;
int n, m, maxa, a[N];
struct Tree
{
    int l, r;
    int sum;
} tree[N * 50];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N], cnt;
inline void update(int pre, int &rt, int l, int r, int pos, int val)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    tree[rt].sum += val;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos, val);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos, val);
}
inline int query(int rootl, int rootr, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rootr].sum - tree[rootl].sum;
    int mid = (l + r) >> 1;
    return query(lc(rootl), lc(rootr), l, mid, x, y) + query(rc(rootl), rc(rootr), mid + 1, r, x, y);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        maxa = max(maxa, a[i]);
    }
    for (int i = 1; i <= n; ++i)
        update(root[i - 1], root[i], 1, maxa, a[i], a[i]);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        read(l, r);
        int x = 0, res;
        while (res = query(root[l - 1], root[r], 1, maxa, 1, x + 1), res > x)
            x = res;
        printf("%d\n", x + 1);
    }
    return 0;
}
