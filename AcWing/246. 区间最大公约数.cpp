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
constexpr int N = 5e5 + 5;
int n, m;
ll a[N], gcd[N * 4], sum[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    sum[rt] = sum[lc] + sum[rc];
    gcd[rt] = __gcd(gcd[lc], gcd[rc]);
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        sum[rt] = gcd[rt] = a[r] - a[l - 1];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos, ll val)
{
    if (l == r)
    {
        sum[rt] += val;
        gcd[rt] += val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline ll query(int rt, int l, int r, int pos)
{
    if (l == r)
        return sum[rt];
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(lc, l, mid, pos);
    else
        return sum[lc] + query(rc, mid + 1, r, pos);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return gcd[rt];
    int mid = (l + r) >> 1;
    return __gcd(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        char opt[5];
        scanf("%s", opt);
        int l, r;
        ll d;
        read(l, r);
        if (opt[0] == 'C')
        {
            read(d);
            update(1, 1, n, l, d);
            if (r < n)
                update(1, 1, n, r + 1, -d);
        }
        else
            printf("%lld\n", abs(__gcd(query(1, 1, n, l), query(1, 1, n, l + 1, r))));
    }
    return 0;
}