#include <bits/stdc++.h>
#define int ll
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
using namespace std;
const int N = 4e5 + 5;
const int mod = 1e9 + 7;
inline ll quickpow(ll a, int b)
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
int n, q, a[N];
int prime[N] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};
inline ll solve(int val)
{
    ll res = 0;
    for (int i = 0; i < 62 && prime[i] <= val; ++i)
        if (val % prime[i] == 0)
        {
            res |= (1ll << i);
            while (val % prime[i] == 0)
                val /= prime[i];
        }
    return res;
}
struct Tree
{
    ll mul, tag, S, tagS;
    int size;
    inline void update(ll val, ll valS)
    {
        (mul *= quickpow(val, size)) %= mod;
        (tag *= val) %= mod;
        tagS |= valS;
        S |= valS;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].mul = tree[lc].mul * tree[rc].mul % mod;
    tree[rt].S = (tree[lc].S | tree[rc].S);
}
inline void pushdown(int rt)
{
    if (tree[rt].tag != 1)
    {
        tree[lc].update(tree[rt].tag, tree[rt].tagS);
        tree[rc].update(tree[rt].tag, tree[rt].tagS);
        tree[rt].tag = 1;
        tree[rt].tagS = 0;
    }
}
inline void build(int rt, int l, int r)
{
    tree[rt].size = r - l + 1;
    tree[rt].tag = 1;
    if (l == r)
    {
        tree[rt].mul = a[l];
        tree[rt].S = solve(a[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y, int val, int valS)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(val, valS);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val, valS);
    update(rc, mid + 1, r, x, y, val, valS);
    pushup(rt);
}
inline ll querymul(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 1;
    if (x <= l && r <= y)
        return tree[rt].mul;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return querymul(lc, l, mid, x, y) * querymul(rc, mid + 1, r, x, y) % mod;
}
inline ll queryS(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].S;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return queryS(lc, l, mid, x, y) | queryS(rc, mid + 1, r, x, y);
}
ll inv[N], need[N];
inline ll calc(ll S)
{
    ll res = 1;
    for (int i = 0; i < 62; ++i)
        if ((S >> i) & 1)
            (res *= need[i]) %= mod;
    return res;
}
signed main()
{
    read(n, q);
    inv[1] = 1;
    for (int i = 2; i <= 300; ++i)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 0; i < 62; ++i)
        need[i] = inv[prime[i]] * (prime[i] - 1) % mod;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    build(1, 1, n);
    while (q--)
    {
        char opt[10];
        scanf("%s", opt);
        int l, r;
        read(l, r);
        if (opt[0] == 'M')
        {
            int x;
            read(x);
            update(1, 1, n, l, r, x, solve(x));
        }
        else
            printf("%lld\n", querymul(1, 1, n, l, r)*calc(queryS(1, 1, n, l, r))%mod);
    }
    return 0;
}