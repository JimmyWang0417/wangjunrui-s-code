/**
 *    unicode: UTF-8
 *    name:    P4721 【模板】分治 FFT
 *    author:  wangjunrui
 *    created: 2022.07.03 周日 00:15:51 (Asia/Shanghai)
 **/
#include <algorithm>
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
constexpr int mod = 998244353;
constexpr int inv3 = (mod + 1) / 3;
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
int n, F[N], G[N];
int limit, len, rk[N];
ll A[N], B[N];
inline void init(int all)
{
    len = 0, limit = 1;
    while (limit <= all)
    {
        limit <<= 1;
        ++len;
    }
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
}
inline void NTT(ll *dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(3, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += mid << 1)
        {
            ll g = 1;
            for (int i = 0; i < mid; ++i, (g *= gn) %= mod)
            {
                ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
                dp[i + j] = (x + y) % mod;
                dp[i + j + mid] = (x - y) % mod;
            }
        }
    }
}
inline void INTT(ll *dp)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(dp[i], dp[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(inv3, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += mid << 1)
        {
            ll g = 1;
            for (int i = 0; i < mid; ++i, (g *= gn) %= mod)
            {
                ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
                dp[i + j] = (x + y) % mod;
                dp[i + j + mid] = (x - y) % mod;
            }
        }
    }
    ll inv = quickpow(limit, mod - 2);
    for (int i = 0; i < limit; ++i)
        (dp[i] *= inv) %= mod;
}
inline void cdq(int l, int r)
{
    if (l == r)
    {
        (F[l] += mod) %= mod;
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid);
    copy(F + l, F + mid + 1, A);
    copy(G + 1, G + (r - l + 1), B + 1);
    for (int i = 1; i <= r - l; ++i)
        B[i] = G[i];
    init(r - l);
    NTT(A), NTT(B);
    for (int i = 0; i < limit; ++i)
        (A[i] *= B[i]) %= mod;
    INTT(A);
    for (int i = mid + 1; i <= r; ++i)
        (F[i] += (int)A[i - l]) %= mod;
    fill(A, A + limit, 0);
    fill(B, B + limit, 0);
    cdq(mid + 1, r);
}
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
        read(G[i]);
    F[0] = 1;
    cdq(0, n - 1);
    for (int i = 0; i < n; ++i)
        printf("%d ", F[i]);
    putchar('\n');
    return 0;
}