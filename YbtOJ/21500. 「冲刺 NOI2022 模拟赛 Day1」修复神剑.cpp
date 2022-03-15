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
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
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
ll fac[N], ifac[N];
int power2[N];
inline ll C(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int n, a, b, c;
inline ll calc(int all)
{
    ll res = 0;
    for (int i = 0; i <= b; ++i)
    {
        int j = i - b + c, k = all - i - j;
        if (j < 0 || k < 0)
            continue;
        (res += C(all, i) * C(all - i, j) % mod * C(b + j - 1, all - 1) % mod * power2[k]) %= mod;
    }
    return res;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("blacksky.in", "r", stdin);
    freopen("blacksky.out", "w", stdout);
#endif
    read(n, a, b, c);
    a = n - a, b = n - b, c = n - c;
    if (a < 0 || b < 0 || c < 0)
        printf("0\n");
    else
    {
        if (a < b)
            swap(a, b);
        if (a < c)
            swap(a, c);
        if (b < c)
            swap(b, c);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n], mod - 2);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
        power2[0] = 1;
        for (int i = 1; i <= n; ++i)
            power2[i] = power2[i - 1] * 2 % mod;
        printf("%lld\n", ((calc(a - 1) + 2 * calc(a) + calc(a + 1)) % mod * 2) % mod);
    }
    return 0;
}
