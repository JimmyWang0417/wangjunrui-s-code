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
constexpr int N = 2e5 + 5;
int n, m;
struct Tree
{
    int size;
    int min;
    int sum;
    int tag;
    inline void update(int val)
    {
        min = tag = val;
        sum = 1000000001 / size < val ? 1000000001 : size * val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].min = min(tree[lc].min, tree[rc].min);
    tree[rt].sum = min(tree[lc].sum + tree[rc].sum, 1000000001);
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
    tree[rt].size = r - l + 1;
    if (l == r)
    {
        read(tree[rt].min);
        tree[rt].sum = tree[rt].min;
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
inline int query(int rt, int l, int r, int x, int &y)
{
    if (r < x || y < tree[rt].min)
        return 0;
    if (l >= x && tree[rt].sum <= y)
    {
        y -= tree[rt].sum;
        return tree[rt].size;
    }
    int mid = (l + r) >> 1, las = 0;
    pushdown(rt);
    if (mid >= x)
        las = query(lc, l, mid, x, y);
    return las + query(rc, mid + 1, r, x, y);
}
inline int find(int rt, int l, int r, int val)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (tree[lc].min < val)
        return find(lc, l, mid, val);
    else
        return find(rc, mid + 1, r, val);
}
signed main()
{
    read(n, m);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y;
        read(opt, x, y);
        if (opt == 1)
        {
            if (tree[1].min < y)
            {
                int pos = find(1, 1, n, y);
                if (pos <= x)
                    update(1, 1, n, pos, x, y);
            }
        }
        else
            printf("%d\n", query(1, 1, n, x, y));
    }
    return 0;
}