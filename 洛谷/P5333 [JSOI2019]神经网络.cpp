/**
 *    unicode: UTF-8
 *    name:    P5333 [JSOI2019]神经网络
 *    author:  whitepaperdog
 *    created: 2022.08.12 周五 15:55:28 (Asia/Shanghai)
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
constexpr int N = 5005, M = 305;
constexpr int mod = 998244353;
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
int n;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int size[N];
ll f[N][N][3], g[N][3], h[N];
inline void dfs(int u, int _fa)
{
    size[u] = 1;
    f[u][1][0] = 1;
    for (int e = head[u]; e; e = edge[e].next)
    {
        int v = edge[e].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        for (int i = 1; i <= size[u]; ++i)
            for (int j = 1; j <= size[v]; ++j)
            {
                (g[i + j][0] += f[u][i][0] * (f[v][j][0] + (f[v][j][1] + f[v][j][2]) * 2)) %= mod;
                (g[i + j][1] += f[u][i][1] * (f[v][j][0] + (f[v][j][1] + f[v][j][2]) * 2)) %= mod;
                (g[i + j][2] += f[u][i][2] * (f[v][j][0] + (f[v][j][1] + f[v][j][2]) * 2)) %= mod;
                (g[i + j - 1][1] += f[u][i][0] * (f[v][j][0] + f[v][j][1])) %= mod;
                (g[i + j - 1][2] += f[u][i][1] * (f[v][j][0] + f[v][j][1])) %= mod;
            }
        size[u] += size[v];
        copy(g[1], g[size[u]] + 1, f[u][1]);
        fill(g[1], g[size[u]] + 1, 0);
    }
}
ll fac[N], ifac[N];
inline ll C(int _x, int _y)
{
    return fac[_x] * ifac[_y] % mod * ifac[_x - _y] % mod;
}
ll F[N], G[N];
signed main()
{
    int T;
    read(T);
    fac[0] = 1;
    for (int i = 1; i <= N - 5; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[N - 5] = quickpow(fac[N - 5], mod - 2);
    for (int i = N - 5; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    int sum = 0;
    for (int kase = 1; kase <= T; ++kase)
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
        if (kase == 1)
        {
            for (int i = 1; i <= n; ++i)
            {
                ll all = (f[1][i][0] + (f[1][i][1] + f[1][i][2]) * 2) * fac[i - 1] % mod;
                for (int j = 1; j <= i; ++j)
                {
                    if ((i + j) & 1)
                        (h[j - 1] -= C(i - 1, j - 1) * all) %= mod;
                    else
                        (h[j - 1] += C(i - 1, j - 1) * all) %= mod;
                }
                for (int j = 2; j <= i; ++j)
                {
                    if ((i + j) & 1)
                        (h[j - 2] += C(i - 1, j - 1) * all) %= mod;
                    else
                        (h[j - 2] -= C(i - 1, j - 1) * all) %= mod;
                }
            }
            for (int i = 0; i < n; ++i)
                (h[i] *= ifac[i]) %= mod;
            copy(h, h + n, F);
            fill(h, h + n, 0);
            sum += n - 1;
        }
        else
        {
            for (int i = 1; i <= n; ++i)
            {
                ll all = (f[1][i][0] + (f[1][i][1] + f[1][i][2]) * 2) * fac[i] % mod;
                for (int j = 1; j <= i; ++j)
                {
                    if ((i + j) & 1)
                        (h[j] -= C(i - 1, j - 1) * all) %= mod;
                    else
                        (h[j] += C(i - 1, j - 1) * all) %= mod;
                }
            }
            for (int i = 1; i <= n; ++i)
                (h[i] *= ifac[i]) %= mod;
            for (int i = 0; i <= sum; ++i)
                for (int j = 0; j <= n; ++j)
                    (G[i + j] += F[i] * h[j]) %= mod;
            sum += n;
            copy(G, G + 1 + sum, F);
            fill(G, G + 1 + sum, 0);
            fill(h + 1, h + 1 + n, 0);
        }
        for (int i = 1; i <= n; ++i)
            fill(f[i][1], f[i][size[i]] + 1, 0);
        fill(head + 1, head + 1 + n, 0);
        num_edge = 0;
    }
    ll res = 0;
    for (int i = 0; i <= sum; ++i)
        (res += F[i] * fac[i]) %= mod;
    printf("%lld\n", (res + mod) % mod);
    return 0;
}