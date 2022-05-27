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
const int N = (1 << 18) + 5;
int n, m, q, a[N];
struct Tree
{
    int dep;
    ll sum;
} tree[N * 4];
bool rev[N];
#define lc ((rt << 1) | (rev[tree[rt].dep]))
#define rc ((rt << 1) | (rev[tree[rt].dep] ^ 1))
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
    tree[rt].dep = tree[lc].dep + 1;
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].sum = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
signed main()
{
    read(n, q);
    m = (1 << n);
    for (int i = 1; i <= m; ++i)
        read(a[i]);
    build(1, 1, m);
    while (q--)
    {
        int opt, x, y;
        read(opt, x);
        if (opt == 1)
        {
            read(y);
            update(1, 1, m, x, y);
        }
        else if (opt == 2)
        {
            for (int i = x; i >= 0; --i)
                rev[i] ^= 1;
        }
        else if (opt == 3)
            rev[x + 1] ^= 1;
        else
        {
            read(y);
            printf("%lld\n", query(1, 1, m, x, y));
        }
    }
    return 0;
}