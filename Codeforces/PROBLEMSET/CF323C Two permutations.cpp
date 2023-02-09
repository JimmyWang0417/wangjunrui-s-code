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
const int N = 1e6 + 5;
int n, m;
struct Point
{
    int x, y;
    inline bool operator<(const Point &rhs) const
    {
        return x < rhs.x;
    }
} point[N];
struct Tree
{
    int l, r;
    int size;
} tree[N * 40];
int root[N], cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void update(int pre, int &rt, int l, int r, int pos)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    ++tree[rt].size;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos);
}
inline int query(int rootl, int rootr, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rootr].size - tree[rootl].size;
    int mid = (l + r) >> 1;
    return query(lc(rootl), lc(rootr), l, mid, x, y) + query(rc(rootl), rc(rootr), mid + 1, r, x, y);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int val;
        read(val);
        point[val].x = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        int val;
        read(val);
        point[val].y = i;
    }
    sort(point + 1, point + 1 + n);
    for (int i = 1; i <= n; ++i)
        update(root[i - 1], root[i], 1, n, point[i].y);
    read(m);
    int lastans = -1;
    for (int i = 1; i <= m; ++i)
    {
        int l1, r1, l2, r2;
        read(l1, r1, l2, r2);

        l1 = (l1 + lastans) % n + 1;
        l2 = (l2 + lastans) % n + 1;
        r1 = (r1 + lastans) % n + 1;
        r2 = (r2 + lastans) % n + 1;
        if (l1 > r1)
            swap(l1, r1);
        if (l2 > r2)
            swap(l2, r2);
        //		printf("%d %d %d %d\n",l1,r1,l2,r2);

        printf("%d\n", lastans = query(root[l1 - 1], root[r1], 1, n, l2, r2));
    }
    return 0;
}
