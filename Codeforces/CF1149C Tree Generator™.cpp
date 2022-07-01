/**
 *    unicode: UTF-8
 *    name:    CF1149C Tree Generator™
 *    author:  wangjunrui
 *    created: 2022.06.28 周二 21:54:12
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
constexpr int N = 2e5 + 5;
int n, m;
char str[N];
struct Tree
{
    int sum;
    int premin, premax;
    int sufmin, sufmax;
    int maxx[3];
    inline Tree operator+(const Tree &rhs) const
    {
        Tree res;
        res.sum = sum + rhs.sum;
        res.premin = min(premin, sum + rhs.premin);
        res.premax = max(premax, sum + rhs.premax);
        res.sufmin = min(sufmin + rhs.sum, rhs.sufmin);
        res.sufmax = max(sufmax + rhs.sum, rhs.sufmax);
        res.maxx[0] = max(maxx[0], max(-sum + rhs.maxx[0], sufmax * 2 - sum + rhs.premax));
        res.maxx[1] = max(rhs.maxx[1], max(maxx[1] + rhs.sum, -sufmin + rhs.sum - 2 * rhs.premin));
        res.maxx[2] = max(max(maxx[2], rhs.maxx[2]), max(maxx[1] + rhs.premax, -sufmin + rhs.maxx[0]));
        return res;
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
    if (l == r)
    {
        if (str[l] == '(')
        {
            tree[rt].sum = 1;
            tree[rt].premin = tree[rt].sufmin = 0;
            tree[rt].premax = tree[rt].sufmax = 1;
        }
        else
        {
            tree[rt].sum = -1;
            tree[rt].premin = tree[rt].sufmin = -1;
            tree[rt].premax = tree[rt].sufmax = 0;
        }
        tree[rt].maxx[0] = tree[rt].maxx[1] = tree[rt].maxx[2] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos)
{
    if (l == r)
    {
        if (str[l] == '(')
        {
            tree[rt].sum = 1;
            tree[rt].premin = tree[rt].sufmin = 0;
            tree[rt].premax = tree[rt].sufmax = 1;
        }
        else
        {
            tree[rt].sum = -1;
            tree[rt].premin = tree[rt].sufmin = -1;
            tree[rt].premax = tree[rt].sufmax = 0;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos);
    else
        update(rc, mid + 1, r, pos);
    pushup(rt);
}
signed main()
{
    read(n, m);
    n = (n - 1) * 2;
    scanf("%s", str + 1);
    build(1, 1, n);
    printf("%d\n", tree[1].maxx[2]);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        if (str[x] != str[y])
        {
            swap(str[x], str[y]);
            update(1, 1, n, x);
            update(1, 1, n, y);
        }
        printf("%d\n", tree[1].maxx[2]);
    }
    return 0;
}