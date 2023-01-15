/**
 *    unicode: UTF-8
 *    name:    CF338E Optimize!
 *    author:  whitepaperdog
 *    created: 2022.07.10 周日 23:23:03 (Asia/Shanghai)
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
int n, len, h;
int a[N], b[N];
int p[N], tot;
struct Tree
{
    int sum, min;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
    tree[rt].min = min(tree[lc].min, tree[lc].sum + tree[rc].min);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].sum += val;
        tree[rt].min += val;
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
    read(n, len, h);
    for (int i = 1; i <= len; ++i)
    {
        read(b[i]);
        b[i] = h - b[i];
        p[++tot] = b[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[++tot] = a[i];
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    for (int i = 1; i <= n; ++i)
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
    for (int i = 1; i <= len; ++i)
        b[i] = (int)(lower_bound(p + 1, p + 1 + tot, b[i]) - p);
    for (int i = 1; i <= len; ++i)
    {
        update(1, 1, tot, a[i], -1);
        update(1, 1, tot, b[i], 1);
    }
    int res = (tree[1].min >= 0);
    for (int i = len + 1; i <= n; ++i)
    {
        update(1, 1, tot, a[i - len], 1);
        update(1, 1, tot, a[i], -1);
        res += (tree[1].min >= 0);
    }
    printf("%d\n", res);
    return 0;
}