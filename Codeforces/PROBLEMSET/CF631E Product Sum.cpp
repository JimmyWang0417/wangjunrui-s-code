#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
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
int n, a[N];
ll sum[N], all;
struct node
{
    int k;
    ll b;
    node(int _k = 0, ll _b = 0) : k(_k), b(_b) {}
    inline ll calc(int x)
    {
        return (ll)k * x + b;
    }
} tree[N * 40];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    tree[rt] = node(0, -1e18);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, node val)
{
    int mid = (l + r) >> 1;
    ll now = val.calc(mid), res = tree[rt].calc(mid);
    if (l == r)
    {
        if (now > res)
            tree[rt] = val;
        return;
    }
    if (val.k > tree[rt].k)
    {
        if (now > res)
        {
            update(lc, l, mid, tree[rt]);
            tree[rt] = val;
        }
        else
            update(rc, mid + 1, r, val);
    }
    else
    {
        if (now > res)
        {
            update(rc, mid + 1, r, tree[rt]);
            tree[rt] = val;
        }
        else
            update(lc, l, mid, val);
    }
}
inline ll query(int rt, int l, int r, int pos)
{
    if (l == r)
        return tree[rt].calc(pos);
    int mid = (l + r) >> 1;
    return max(tree[rt].calc(pos), (pos <= mid ? query(lc, l, mid, pos) : query(rc, mid + 1, r, pos)));
}
signed main()
{
    int minn = INT_MAX, maxx = INT_MIN;
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        sum[i] = sum[i - 1] + a[i];
        all += (ll)i * a[i];
        ckmin(minn, a[i]);
        ckmax(maxx, a[i]);
    }
    ll ans = 0;
    build(1, minn, maxx);
    for (int i = 1; i <= n; ++i)
    {
        ckmax(ans, sum[i - 1] - (ll)i * a[i] + query(1, minn, maxx, a[i]));
        update(1, minn, maxx, node(i, -sum[i - 1]));
    }
    build(1, minn, maxx);
    for (int i = n; i >= 1; --i)
    {
        ckmax(ans, sum[i] - (ll)i * a[i] + query(1, minn, maxx, a[i]));
        update(1, minn, maxx, node(i, -sum[i]));
    }
    printf("%lld\n", all + ans);
    return 0;
}