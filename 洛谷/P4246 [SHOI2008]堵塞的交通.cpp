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
bool exist[N][2];
struct Tree
{
    int right;
    bool l, r, u, d, p, q;
    Tree()
    {
        right = l = r = u = d = p = q = 0;
    }
    inline Tree friend operator+(const Tree a, const Tree b)
    {
        Tree rt;
        rt.right = b.right;

        rt.l = a.l || (a.u && exist[a.right][0] && b.l && exist[a.right][1] && a.d);
        rt.r = b.r || (b.u && exist[a.right][0] && a.r && exist[a.right][1] && b.d);

        rt.u = (a.u && exist[a.right][0] && b.u) || (a.p && exist[a.right][1] && b.q);
        rt.d = (a.d && exist[a.right][1] && b.d) || (a.q && exist[a.right][0] && b.p);

        rt.p = (a.u && exist[a.right][0] && b.p) || (a.p && exist[a.right][1] && b.d);
        rt.q = (a.d && exist[a.right][1] && b.q) || (a.q && exist[a.right][0] && b.u);
        return rt;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt] = tree[lc] + tree[rc];
}
inline void build(int rt, int l, int r)
{
    tree[rt].right = r;
    if (l == r)
    {
        tree[rt].u = tree[rt].d = true;
        tree[rt].l = tree[rt].r = tree[rt].p = tree[rt].q = false;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update1(int rt, int l, int r, int pos, bool row, bool val)
{
    int mid = (l + r) >> 1;
    if (mid == pos)
    {
        exist[mid][row] = val;
        pushup(rt);
        return;
    }
    if (pos <= mid)
        update1(lc, l, mid, pos, row, val);
    else
        update1(rc, mid + 1, r, pos, row, val);
    pushup(rt);
}
inline void update2(int rt, int l, int r, int pos, bool val)
{
    if (l == r)
    {
        tree[rt].l = tree[rt].r = tree[rt].p = tree[rt].q = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update2(lc, l, mid, pos, val);
    else
        update2(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline Tree query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    if (mid < x)
        return query(rc, mid + 1, r, x, y);
    if (y <= mid)
        return query(lc, l, mid, x, y);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
int n;
signed main()
{
    read(n);
    build(1, 1, n);
    char opt[10];
    while (scanf("%s", opt) != EOF && opt[0] != 'E')
    {
        int r1, r2;
        int x, y;
        read(r1, x, r2, y);
        --r1, --r2;
        if (x > y)
        {
            swap(r1, r2);
            swap(x, y);
        }
        if (opt[0] == 'O')
        {
            if (r1 == r2)
                update1(1, 1, n, x, r1, true);
            else
                update2(1, 1, n, x, true);
        }
        else if (opt[0] == 'C')
        {
            if (r1 == r2)
                update1(1, 1, n, x, r1, false);
            else
                update2(1, 1, n, x, false);
        }
        else if (opt[0] == 'A')
        {
            Tree left = query(1, 1, n, 1, x), res = query(1, 1, n, x, y), right = query(1, 1, n, y, n);
            if (r1)
            {
                if (r2)
                {
                    if (res.d || (left.r && res.u && right.l))
                        puts("Y");
                    else
                        puts("N");
                }
                else
                {
                    if (res.q || (left.r && res.u) || (res.d && right.l))
                        puts("Y");
                    else
                        puts("N");
                }
            }
            else
            {
                if (r2)
                {
                    if (res.p || (left.r && res.d) || (right.l && res.u))
                        puts("Y");
                    else
                        puts("N");
                }
                else
                {
                    if (res.u || (left.r && res.d && right.l))
                        puts("Y");
                    else
                        puts("N");
                }
            }
        }
    }
    return 0;
}
