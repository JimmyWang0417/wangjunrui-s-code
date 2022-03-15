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
constexpr int N = 5e3 + 5;
constexpr int mod = 1e9 + 7;
template <typename T>
inline void dec(T &x, T y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
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
int n, k;
ll a[N];
inline void solve(int x, int len)
{
    for (int i = len - 1; i >= 0; --i)
    {
        dec(a[i + 1], a[i]);
        a[i] = (a[i] * x) % mod;
    }
}
signed main()
{
    freopen("calculate.in", "r", stdin);
    freopen("calculate.out", "w", stdout);
    read(n, k);
    a[0] = 1;
    ll all = 1;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        solve(x, i);
        (all *= x) %= mod;
    }
    ll ans = 0, invn = quickpow(n, mod - 2), now = 1;
    for (int i = 0; i <= min(n, k); ++i)
    {
        (ans += a[i] * now) %= mod;
        now = now * (k - i) % mod * invn % mod;
    }
    dec(all, ans);
    printf("%lld\n", all);
    return 0;
}