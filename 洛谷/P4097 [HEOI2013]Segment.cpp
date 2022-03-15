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
const int N = 1e6 + 5;
const int mod = 39989, maxx = 1e9;
int n;
struct node
{
    double k, b;
    inline double calc(int x)
    {
        return k * x + b;
    }
} a[N * 2];
int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void newnode(int rt, int x1, int y1, int x2, int y2)
{
    if (x1 == x2)
    {
        a[rt].k = 0;
        a[rt].b = max(y1, y2);
    }
    else
    {
        a[rt].k = (double)(y2 - y1) / (x2 - x1);
        a[rt].b = y1 - x1 * a[rt].k;
    }
}
inline void update(int rt, int l, int r, int x, int y, int id)
{
    if (r < x || l > y)
        return;
    int mid = (l + r) >> 1;
    if (x <= l && r <= y)
    {
        double res = a[id].calc(mid), ans = a[tree[rt]].calc(mid);
        if (l == r)
        {
            if (res > ans)
                tree[rt] = id;
            return;
        }
        if (a[tree[rt]].k < a[id].k)
        {
            if (res > ans)
            {
                update(lc, l, mid, x, y, tree[rt]);
                tree[rt] = id;
            }
            else
                update(rc, mid + 1, r, x, y, id);
        }
        else if (a[tree[rt]].k > a[id].k)
        {
            if (res > ans)
            {
                update(rc, mid + 1, r, x, y, tree[rt]);
                tree[rt] = id;
            }
            else
                update(lc, l, mid, x, y, id);
        }
        else
        {
            if (a[tree[rt]].b < a[id].b)
                tree[rt] = id;
        }
        return;
    }
    update(lc, l, mid, x, y, id);
    update(rc, mid + 1, r, x, y, id);
}
inline pair<double, int> getans(const pair<double, int> &lhs, const pair<double, int> &rhs)
{
    if (lhs.first < rhs.first)
        return rhs;
    else if (lhs.first > rhs.first)
        return lhs;
    else
        return lhs.second < rhs.second ? lhs : rhs;
}
inline pair<double, int> query(int rt, int l, int r, int pos)
{
    if (l == r)
        return make_pair(a[tree[rt]].calc(pos), tree[rt]);
    int mid = (l + r) >> 1;
    return getans(make_pair(a[tree[rt]].calc(pos), tree[rt]), pos <= mid ? query(lc, l, mid, pos) : query(rc, mid + 1, r, pos));
}
signed main()
{
    a[0].b = -1e18;
    read(n);
    int ctime = 0;
    int lastans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int opt;
        read(opt);
        if (opt == 1)
        {
            int x1, y1, x2, y2;
            read(x1, y1, x2, y2);
            x1 = (x1 + lastans - 1) % mod + 1;
            y1 = (y1 + lastans - 1) % maxx + 1;
            x2 = (x2 + lastans - 1) % mod + 1;
            y2 = (y2 + lastans - 1) % maxx + 1;
            newnode(++ctime, x1, y1, x2, y2);
            if (x1 > x2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            update(1, 1, mod, x1, x2, ctime);
        }
        else
        {
            int x;
            read(x);
            x = (x + lastans - 1) % mod + 1;
            printf("%d\n", lastans = query(1, 1, mod, x).second);
        }
    }
    return 0;
}