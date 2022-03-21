#include <algorithm>
#include <cstdio>
#include <vector>
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
constexpr int mod = 1e9 + 7;
inline ll quickpow(ll a, int b = mod - 2)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
int n;
pair<int, int> a[N];
struct Tree
{
    ll sum, mul;
    inline void update(ll val)
    {
        (sum *= val) %= mod;
        (mul *= val) %= mod;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].sum = (tree[lc].sum + tree[rc].sum) % mod;
}
inline void pushdown(int rt)
{
    if (tree[rt].mul != 1)
    {
        tree[lc].update(tree[rt].mul);
        tree[rc].update(tree[rt].mul);
        tree[rt].mul = 1;
    }
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].sum = val;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline ll query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return (query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y)) % mod;
}
int c[N];
inline void update(int pos)
{
    for (int i = pos; i <= n; i += lowbit(i))
        ++c[i];
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += c[i];
    return res;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].first);
        a[i].second = i;
    }
    sort(a + 1, a + 1 + n);
    ll all = 1;
    for (int i = 1; i <= n; ++i)
        (all *= (a[i].first - i + 1)) %= mod;
    ll res = 0;
    for (int i = 1; i <= n; ++i)
    {
        ll now = (query(1, 1, n, 1, a[i].second - 1) - query(1, 1, n, a[i].second + 1, n)) % mod;
        (now *= all * quickpow(2 * (a[i].first - i + 1)) % mod) %= mod;
        (res += now + (query(n) - query(a[i].second)) * all % mod) %= mod;
        tree[1].update((a[i].first - i) * quickpow(a[i].first - i + 1) % mod);
        update(1, 1, n, a[i].second, a[i].first - i);
        update(a[i].second);
    }
    printf("%lld\n", (res + mod) % mod);
    return 0;
}