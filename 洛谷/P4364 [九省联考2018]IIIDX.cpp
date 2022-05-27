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
const int N = 5e5 + 5;
struct Tree
{
    int tag;
    int min;
    inline void update(int val)
    {
        tag += val;
        min += val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].min = min(tree[lc].min, tree[rc].min);
}
inline void pushdown(int rt)
{
    if (tree[rt].tag)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].min = l;
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
    {
        tree[rt].update(val);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline int query(int rt, int l, int r, int val)
{
    if (l == r)
        return tree[rt].min >= val ? l : l + 1;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (tree[rc].min >= val)
        return query(lc, l, mid, val);
    else
        return query(rc, mid + 1, r, val);
}
int n;
double k;
int a[N];
int cnt[N];
int fa[N], size[N];
int ans[N];
signed main()
{
    read(n);
    scanf("%lf", &k);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    sort(a + 1, a + 1 + n, greater<int>());
    for (int i = n; i >= 1; --i)
    {
        fa[i] = (int)floor(i / k);
        size[fa[i]] += (++size[i]);
    }
    for (int i = n; i >= 1; --i)
        if (a[i] != a[i + 1])
            cnt[i] = 0;
        else
            cnt[i] = cnt[i + 1] + 1;
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        if (fa[i] != fa[i - 1])
            update(1, 1, n, ans[fa[i]], n, size[fa[i]] - 1);
        int &x = ans[i] = query(1, 1, n, size[i]);
        x += cnt[x], x -= (cnt[x]++);
        update(1, 1, n, ans[i], n, -size[i]);
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[ans[i]]);
    putchar('\n');
    return 0;
}
