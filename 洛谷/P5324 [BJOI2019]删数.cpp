/**
 *    unicode: UTF-8
 *    name:    P5324 [BJOI2019]删数
 *    author:  wangjunrui
 *    created: 2022.07.24 周日 15:40:43 (Asia/Shanghai)
 **/
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
constexpr int N = 1.5e5 + 5, M = 6e5 + 5;
int n, m, limit, a[N];
int buf[N * 3], *b = &buf[N];
struct Tree
{
    int min, cnt;
    int tag;
    inline void update(int val)
    {
        tag += val;
        min += val;
    }
} tree[M * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].min = tree[lc].min;
    tree[rt].cnt = tree[lc].cnt;
    if (tree[rt].min > tree[rc].min)
    {
        tree[rt].min = tree[rc].min;
        tree[rt].cnt = tree[rc].cnt;
    }
    else if (tree[rt].min == tree[rc].min)
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
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].min += val;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
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
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y || tree[rt].min > 0)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].cnt;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
inline int query(int rt, int l, int r, int pos)
{
    if (l == r)
        return tree[rt].min;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        return query(lc, l, mid, pos);
    else
        return query(rc, mid + 1, r, pos);
}
signed main()
{
    read(n, m);
    limit = n + m;
    build(1, -limit, limit);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        update(1, -limit, limit, a[i] - (b[a[i]]++), 1);
    }
    int tag = 0;
    for (int i = 1; i <= m; ++i)
    {
        int pos, val;
        read(pos, val);
        if (pos)
        {
            if (a[pos] + tag <= n)
                update(1, -limit, limit, a[pos] - (b[a[pos]] - 1), -1);
            --b[a[pos]];
            a[pos] = val - tag;
            ++b[a[pos]];
            update(1, -limit, limit, a[pos] - (b[a[pos]] - 1), 1);
        }
        else
        {
            if (val == 1)
            {
                update(1, -limit, limit, n - tag - (b[n - tag] - 1), n - tag, -1);
                ++tag;
            }
            else
            {
                --tag;
                update(1, -limit, limit, n - tag - (b[n - tag] - 1), n - tag, 1);
            }
        }
        printf("%d\n", query(1, -limit, limit, 1 - tag, n - tag));
    }
    return 0;
}