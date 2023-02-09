#include <bits/stdc++.h>
#define eps (1e-10)
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
struct Tree
{
    int l, r;
    int size;
} tree[N * 50];
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
struct Point
{
    int x, y;
    inline bool operator<(const Point &rhs) const
    {
        return x < rhs.x;
    }
    inline bool operator>(const Point &rhs) const
    {
        return y < rhs.y;
    }
} point[N];
int X[N], Y[N];
int n, a[13];
int p[N], tot;
int linex1, linex2, liney1, liney2;
inline bool check()
{
    //	printf("%d %d\n%d %d\n",linex1,linex2,liney1,liney2);
    //	printf("%d %d %d\n%d %d %d\n%d %d %d\n",
    //	       query(root[0],root[linex1],1,tot,1,liney1),
    //	       query(root[0],root[linex1],1,tot,liney1+1,liney2),
    //	       query(root[0],root[linex1],1,tot,liney2+1,tot),
    //
    //	       query(root[linex1],root[linex2],1,tot,1,liney1),
    //	       query(root[linex1],root[linex2],1,tot,liney1+1,liney2),
    //	       query(root[linex1],root[linex2],1,tot,liney2+1,tot),
    //
    //	       query(root[linex2],root[n],1,tot,1,liney1),
    //	       query(root[linex2],root[n],1,tot,liney1+1,liney2),
    //	       query(root[linex2],root[n],1,tot,liney2+1,tot));
    return query(root[0], root[linex1], 1, tot, 1, Y[liney1]) == a[1] && query(root[0], root[linex1], 1, tot, Y[liney1] + 1, Y[liney2]) == a[2] && query(root[0], root[linex1], 1, tot, Y[liney2] + 1, tot) == a[3]

           && query(root[linex1], root[linex2], 1, tot, 1, Y[liney1]) == a[4] && query(root[linex1], root[linex2], 1, tot, Y[liney1] + 1, Y[liney2]) == a[5] && query(root[linex1], root[linex2], 1, tot, Y[liney2] + 1, tot) == a[6]

           && query(root[linex2], root[n], 1, tot, 1, Y[liney1]) == a[7] && query(root[linex2], root[n], 1, tot, Y[liney1] + 1, Y[liney2]) == a[8] && query(root[linex2], root[n], 1, tot, Y[liney2] + 1, tot) == a[9];
}
inline bool solve()
{
    int k;

    k = a[1] + a[2] + a[3];
    if (X[k] == X[k + 1])
        return false;
    linex1 = k;

    k += a[4] + a[5] + a[6];
    if (X[k] == X[k + 1])
        return false;
    linex2 = k;

    k = a[1] + a[4] + a[7];
    if (Y[k] == Y[k + 1])
        return false;
    liney1 = k;

    k += a[2] + a[5] + a[8];
    if (Y[k] == Y[k + 1])
        return false;
    liney2 = k;

    return check();
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(point[i].x, point[i].y);
        X[i] = point[i].x;
        p[i] = point[i].y;
    }

    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
        Y[i] = point[i].y = (int)(lower_bound(p + 1, p + 1 + tot, point[i].y) - p);

    sort(X + 1, X + 1 + n);
    sort(Y + 1, Y + 1 + n);
    sort(point + 1, point + 1 + n);

    //	printf("wdnmd\n");
    for (int i = 1; i <= n; ++i)
        update(root[i - 1], root[i], 1, tot, point[i].y);
    //	printf("%d\n",query(root[0],root[3],1,tot,1,1));

    //	printf("nmsl\n");

    for (int i = 1; i <= 9; ++i)
        read(a[i]);
    sort(a + 1, a + 10);
    do
    {
        if (solve())
        {
            printf("%lf %lf\n%lf %lf\n",
                   (X[linex1] + X[linex1 + 1]) / 2.0, (X[linex2] + X[linex2 + 1]) / 2.0,
                   (p[Y[liney1]] + p[Y[liney1 + 1]]) / 2.0, (p[Y[liney2]] + p[Y[liney2 + 1]]) / 2.0);
            return 0;
        }
    } while (next_permutation(a + 1, a + 10));
    printf("-1\n");
    return 0;
}
