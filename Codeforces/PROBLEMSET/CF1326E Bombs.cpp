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
template <typename T>
inline void ckmax(T &x, T y)
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
struct Tree
{
    int max;
    int tag;
    inline void update(int val)
    {
        max += val;
        tag += val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].max = max(tree[lc].max, tree[rc].max);
}
inline void pushdown(int rt)
{
    if (tree[rt].tag)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
        return;
    }
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
int n, a[N], b[N], pos[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        pos[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    int res = n;
    update(1, 1, n, 1, pos[n], 1);
    printf("%d", n);
    for (int i = 1; i < n; ++i)
    {
        update(1, 1, n, 1, b[i], -1);
        while (tree[1].max <= 0)
            update(1, 1, n, 1, pos[--res], 1);
        printf(" %d", res);
    }
    putchar('\n');
    return 0;
}