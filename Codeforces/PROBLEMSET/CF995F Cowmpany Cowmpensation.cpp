/**
 *    unicode: UTF-8
 *    name:    CF995F Cowmpany Cowmpensation
 *    author:  whitepaperdog
 *    created: 2022.07.08 周五 13:32:38 (Asia/Shanghai)
 **/
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
constexpr int N = 3005;
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
int n, m, limit;
ll dp[N][N];
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
inline void dfs(int u, int _fa)
{
    for (int i = 1; i <= limit; ++i)
        dp[u][i] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        for (int j = 1; j <= limit; ++j)
            (dp[u][j] *= dp[v][j]) %= mod;
    }
    for (int i = 1; i <= limit; ++i)
        (dp[u][i] += dp[u][i - 1]) %= mod;
}
ll pre[N], suf[N], fac[N], ifac[N];
inline ll solve(int x)
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    pre[0] = 1;
    for (int i = 0; i < n; ++i)
        pre[i + 1] = pre[i] * (x - i) % mod;
    suf[n] = 1;
    for (int i = n; i >= 1; --i)
        suf[i - 1] = suf[i] * (x - i) % mod;
    ll res = 0;
    for (int i = 0; i <= n; ++i)
        if ((n - i) & 1)
            (res -= pre[i] * suf[i] % mod * ifac[i] % mod * ifac[n - i] % mod * dp[1][i]) %= mod;
        else
            (res += pre[i] * suf[i] % mod * ifac[i] % mod * ifac[n - i] % mod * dp[1][i]) %= mod;
    return (res + mod) % mod;
}
signed main()
{
    read(n, m);
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        read(fa);
        add_edge(fa, i);
    }
    limit = min(n, m);
    dfs(1, 0);
    if (n >= m)
        printf("%lld\n", dp[1][m]);
    else
        printf("%lld\n", solve(m));
    return 0;
}