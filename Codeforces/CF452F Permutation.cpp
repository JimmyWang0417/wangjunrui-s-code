/**
 *    unicode: UTF-8
 *    name:    CF452F Permutation
 *    author:  whitepaperdog
 *    created: 2022.07.04 周一 21:13:38 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#define ll long long
#define lll __int128
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
constexpr int N = 3e5 + 5;
int n, a[N];
ull power[N];
struct Tree
{
    int size;
    ull pre, suf;
    inline Tree operator+(const Tree &rhs) const
    {
        Tree res;
        res.size = size + rhs.size;
        res.pre = pre * power[rhs.size] + rhs.pre;
        res.suf = suf + power[size] * rhs.suf;
        return res;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    tree[rt].size = r - l + 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void pushup(int rt)
{
    tree[rt] = tree[lc] + tree[rc];
}
inline void update(int rt, int l, int r, int pos)
{
    if (l == r)
    {
        tree[rt].pre = tree[rt].suf = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos);
    else
        update(rc, mid + 1, r, pos);
    pushup(rt);
}
inline Tree query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    if (y <= mid)
        return query(lc, l, mid, x, y);
    if (x > mid)
        return query(rc, mid + 1, r, x, y);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
signed main()
{
    read(n);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power[i] = power[i - 1] * 31;
        read(a[i]);
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        if (i > 1 && i < n && a[i] > 1 && a[i] < n)
        {
            int len = min(a[i] - 1, n - a[i]);
            if (query(1, 1, n, a[i] - len, a[i] - 1).pre != query(1, 1, n, a[i] + 1, a[i] + len).suf)
            {
                puts("YES");
                return 0;
            }
        }
        update(1, 1, n, a[i]);
    }
    puts("NO");
    return 0;
}