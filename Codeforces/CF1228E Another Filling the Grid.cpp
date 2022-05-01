// Problem: E. Another Filling the Grid
// Contest: Codeforces - Codeforces Round #589 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1228/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
constexpr int N = 1e5 + 5, mod = 1e9 + 7;
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
inline ll C(int n, int m)
{
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int n, m;
signed main()
{
    read(n, m);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    ll answer = 0;
    for (int i = 0; i <= n; ++i)
    {
        if (i & 1)
            (answer -= C(n, i) % mod * quickpow((quickpow(m, n - i) * quickpow(m - 1, i) % mod - quickpow(m - 1, n)), n)) %= mod;
        else
            (answer += C(n, i) % mod * quickpow((quickpow(m, n - i) * quickpow(m - 1, i) % mod - quickpow(m - 1, n)), n)) %= mod;
    }
    printf("%lld\n", (answer + mod) % mod);
    return 0;
}
