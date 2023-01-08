// Problem: E - High Elements
// Contest: AtCoder - AtCoder Grand Contest 028
// URL: https://atcoder.jp/contests/agc028/tasks/agc028_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
constexpr int N = 2e5 + 5;
int n, a[N], b[N];
int suf[N];
class segment_tree
{
public:
    int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    inline void pushup(int rt)
    {
        tree[rt] = max(tree[lc], tree[rc]);
    }
    inline void build(int rt, int l, int r)
    {
        if (l == r)
        {
            tree[rt] = INT_MIN;
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
    inline int query(int rt, int l, int r, int pos)
    {
        if (r < pos)
            return INT_MIN;
        if (pos <= l)
            return tree[rt];
        int mid = (l + r) >> 1;
        return max(query(lc, l, mid, pos), query(rc, mid + 1, r, pos));
    }
} tree1, tree2;
inline bool check(int x, int y)
{
    if (y < 0)
        return false;
    else if (y & 1)
        return tree1.query(1, 1, n, x) >= y;
    else
        return tree2.query(1, 1, n, x) >= y;
}
char answer[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("value.in", "r", stdin);
    freopen("value.out", "w", stdout);
#endif
    read(n);
    for (int i = 1, maxx = 0; i <= n; ++i)
    {
        read(a[i]);
        if (a[i] > maxx)
        {
            maxx = a[i];
            b[i] = 2;
        }
        else
            b[i] = 1;
    }
    tree1.build(1, 1, n);
    for (int i = n; i >= 1; --i)
    {
        suf[i] = suf[i + 1] + b[i] - 1;
        int res1 = tree1.query(1, 1, n, a[i]), res2 = tree2.query(1, 1, n, a[i]);
        if (b[i] & 1)
        {
            tree1.update(1, 1, n, a[i], res2 + b[i]);
            tree2.update(1, 1, n, a[i], res1 + b[i]);
        }
        else
        {
            tree1.update(1, 1, n, a[i], res1 + b[i]);
            tree2.update(1, 1, n, a[i], res2 + b[i]);
        }
    }
    int maxx = 0, maxy = 0, resx = 0, resy = 0;
    for (int i = 1; i <= n; ++i)
    {
        tree1.update(1, 1, n, a[i], INT_MIN), tree2.update(1, 1, n, a[i], 0);
        if (check(maxy, resx - resy + (a[i] > maxx) + suf[i + 1]) || check(maxx, resy - resx - (a[i] > maxx) + suf[i + 1]))
        {
            if (a[i] > maxx)
            {
                ++resx;
                maxx = a[i];
            }
            answer[i] = 'A';
        }
        else
        {
            if (a[i] > maxy)
            {
                ++resy;
                maxy = a[i];
            }
            answer[i] = 'B';
        }
    }
    if (resx != resy)
        puts("NIE");
    else
        printf("%s\n", answer + 1);
    return 0;
}