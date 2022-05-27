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
const int N = 2e5 + 5;
class segment_tree
{
public:
    int a[N];
    int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    inline void init()
    {
        memset(tree, ~0x3f, sizeof(tree));
    }
    inline void pushup(int rt)
    {
        tree[rt] = max(tree[lc], tree[rc]);
    }
    inline void build(int rt, int l, int r)
    {
        if (l == r)
        {
            tree[rt] = a[l];
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
            tree[rt] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc, l, mid, pos, val);
        else
            update(rc, mid + 1, r, pos, val);
        pushup(rt);
    }
    inline int query(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return ~0x7fffffff;
        if (x <= l && r <= y)
            return tree[rt];
        int mid = (l + r) >> 1;
        return max(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
    }
} tree[32];
int n, m, q;
struct Point
{
    int a[6];
    Point()
    {
        memset(a, 0, sizeof(a));
    }
    inline int calc(int S)
    {
        int res = 0;
        for (int i = 0; i < m; ++i)
            if ((S >> i) & 1)
                res += a[i];
            else
                res -= a[i];
        return res;
    }
} point[N];
inline void work()
{
    int opt;
    read(opt);
    if (opt == 1)
    {
        int pos;
        Point x;
        read(pos);
        for (int i = 0; i < m; ++i)
            read(x.a[i]);
        for (int i = 0; i < (1 << m); ++i)
            tree[i].update(1, 1, n, pos, x.calc(i));
    }
    else if (opt == 2)
    {
        int l, r;
        read(l, r);
        int ans = 0;
        for (int i = 0; i < 1 << (m - 1); ++i)
            ans = max(ans, tree[i].query(1, 1, n, l, r) + tree[(1 << m) - i - 1].query(1, 1, n, l, r));
        printf("%d\n", ans);
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < m; ++j)
            read(point[i].a[j]);
        for (int j = 0; j < (1 << m); ++j)
            tree[j].a[i] = point[i].calc(j);
    }
    for (int i = 0; i < (1 << m); ++i)
    {
        tree[i].init();
        tree[i].build(1, 1, n);
    }
    read(q);
    while (q--)
        work();
    return 0;
}
