#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353, inv2 = (mod + 1) / 2;
constexpr int n = 2e5, block = 114514 / 258;
template <typename T>
inline void add(T &x, T y)
{
    (x += y);
    if (x >= mod)
        x -= mod;
}
template <typename T>
inline void dec(T &x, T y)
{
    (x -= y);
    if (x < 0)
        x += mod;
}
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
int m;
int belong[N];
struct node
{
    int l, r, id;
    bool flag;
    inline bool operator<(const node &rhs) const
    {
        return belong[r] == belong[rhs.r] ? (belong[r] & 1 ? l < rhs.l : l > rhs.l) : r < rhs.r;
    }
} a[N];
ll fac[N], inv[N];
inline ll C(int x, int y)
{
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
}
int answer[N];
signed main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    inv[n] = quickpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= n; ++i)
        belong[i] = (i - 1) / block + 1;
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r, x;
        read(l, r, x);
        a[i * 2 - 1].l = x, a[i * 2 - 1].r = r, a[i * 2 - 1].id = i, a[i * 2 - 1].flag = true;
        a[i * 2].l = x, a[i * 2].r = l - 1, a[i * 2].id = i;
    }
    int l = 0, r = 0;
    ll res = C(0, 0);
    sort(a + 1, a + 1 + 2 * m);
    for (int i = 1; i <= 2 * m; ++i)
    {
        int ql = a[i].l, qr = a[i].r;
        while (ql > l)
        {
            add(res, res);
            dec(res, C(l, r));
            ++l;
        }
        while (qr < r)
        {
            dec(res, C(l, r));
            --r;
        }
        while (ql < l)
        {
            --l;
            res = (res + C(l, r)) * inv2 % mod;
        }
        while (qr > r)
        {
            ++r;
            add(res, C(l, r));
        }
        if (a[i].flag)
            add(answer[a[i].id], (int)res);
        else
            dec(answer[a[i].id], (int)res);
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}
