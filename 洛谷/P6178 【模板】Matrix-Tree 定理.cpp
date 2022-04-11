#include <algorithm>
#include <cstdio>
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
constexpr int N = 305;
constexpr int mod = 1e9 + 7;
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
int n, m;
ll g[N][N];
inline void solve()
{
    bool flag = false;
    for (int i = 2; i <= n; ++i)
    {
        int where = 0;
        for (int j = i; j <= n; ++j)
            if (g[j][i])
            {
                where = j;
                break;
            }
        if (where != i)
        {
            swap(g[where], g[i]);
            flag = false;
        }
        ll inv = quickpow(g[i][i]);
        for (int j = i + 1; j <= n; ++j)
        {
            ll times = inv * g[j][i] % mod;
            for (int k = i; k <= n; ++k)
                (g[j][k] -= times * g[i][k] % mod) %= mod;
        }
    }
    ll answer = 1;
    for (int i = 2; i <= n; ++i)
        (answer *= g[i][i]) %= mod;
    if (flag)
        answer = -answer;
    printf("%lld\n", (answer + mod) % mod);
}
signed main()
{
    int type;
    read(n, m, type);
    if (!type)
        for (int i = 1; i <= m; ++i)
        {
            int u, v, w;
            read(u, v, w);
            (g[u][v] -= w) %= mod;
            (g[v][u] -= w) %= mod;
            (g[u][u] += w) %= mod;
            (g[v][v] += w) %= mod;
        }
    else
        for (int i = 1; i <= m; ++i)
        {
            int u, v, w;
            read(u, v, w);
            (g[u][v] -= w) %= mod;
            (g[v][v] += w) %= mod;
        }
    solve();
    return 0;
}