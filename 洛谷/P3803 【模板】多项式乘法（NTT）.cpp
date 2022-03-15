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
constexpr int N = 4e6 + 5;
constexpr int mod = 998244353, inv3 = (mod + 1) / 3;
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
int n, m;
int rk[N];
ll a[N], b[N], c[N];
int limit, len;
inline void FFT(ll *A)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(A[i], A[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(3, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += (mid << 1))
        {
            ll g = 1;
            for (int i = 0; i < mid; ++i, (g *= gn) %= mod)
            {
                ll x = A[i + j], y = A[i + j + mid] * g % mod;
                A[i + j] = (x + y) % mod;
                A[i + j + mid] = (x - y) % mod;
            }
        }
    }
}
inline void IFFT(ll *A)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(A[i], A[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(inv3, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += (mid << 1))
        {
            ll g = 1;
            for (int i = 0; i < mid; ++i, (g *= gn) %= mod)
            {
                ll x = A[i + j], y = A[i + j + mid] * g % mod;
                A[i + j] = (x + y) % mod;
                A[i + j + mid] = (x - y) % mod;
            }
        }
    }
}
signed main()
{
    read(n, m);
    for (int i = 0; i <= n; ++i)
        read(a[i]);
    for (int i = 0; i <= m; ++i)
        read(b[i]);
    len = 0, limit = 1;
    while (limit <= n + m)
    {
        limit <<= 1;
        ++len;
    }
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    FFT(a), FFT(b);
    for (int i = 0; i < limit; ++i)
        c[i] = a[i] * b[i] % mod;
    IFFT(c);
    ll inv = quickpow(limit, mod - 2);
    for (int i = 0; i <= n + m; ++i)
        printf("%lld ", (c[i] * inv % mod + mod) % mod);
    putchar('\n');
    return 0;
}