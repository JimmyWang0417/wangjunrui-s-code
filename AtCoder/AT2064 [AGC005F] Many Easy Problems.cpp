#include <algorithm>
#include <cstdio>
#define size qwq
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
constexpr int N = 8e5 + 5;
constexpr int mod = 924844033;
constexpr int inv5 = 554906420;
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
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int size[N];
int cnt[N];
inline void dfs(int u, int _fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        size[u] += size[v];
    }
    ++cnt[size[u]];
    ++cnt[n - size[u]];
}
ll fac[N], ifac[N];
int limit, len, rk[N];
inline void NTT(ll *A)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(A[i], A[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(5, (mod - 1) / (mid << 1));
        for (int i = 0; i < limit; i += (mid << 1))
        {
            ll g = 1;
            for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
            {
                ll x = A[i + j], y = A[i + j + mid] * g % mod;
                A[i + j] = (x + y) % mod;
                A[i + j + mid] = (x - y) % mod;
            }
        }
    }
}
inline void INTT(ll *A)
{
    for (int i = 0; i < limit; ++i)
        if (i < rk[i])
            swap(A[i], A[rk[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll gn = quickpow(inv5, (mod - 1) / (mid << 1));
        for (int i = 0; i < limit; i += (mid << 1))
        {
            ll g = 1;
            for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
            {
                ll x = A[i + j], y = A[i + j + mid] * g % mod;
                A[i + j] = (x + y) % mod;
                A[i + j + mid] = (x - y) % mod;
            }
        }
    }
    ll inv = quickpow(limit);
    for (int i = 0; i < limit; ++i)
        (A[i] *= inv) %= mod;
}
ll a[N], b[N];
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    len = 0, limit = 1;
    while (limit <= 2 * n)
    {
        limit <<= 1;
        ++len;
    }
    for (int i = 0; i < limit; ++i)
        rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    cnt[0] = cnt[n] = 0;
    for (int i = 0; i <= n; ++i)
    {
        a[i] = cnt[i] * fac[i] % mod;
        b[i] = ifac[n - i];
    }
    NTT(a), NTT(b);
    for (int i = 0; i < limit; ++i)
        (a[i] *= b[i]) %= mod;
    INTT(a);
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ((n * fac[n] % mod * ifac[i] % mod * ifac[n - i] - ifac[i] * a[i + n]) % mod + mod) % mod);
    return 0;
}
