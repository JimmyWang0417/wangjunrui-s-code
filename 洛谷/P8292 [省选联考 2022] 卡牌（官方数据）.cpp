#include <cstdio>
#include <cstring>
#include <vector>
#define int ll
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
constexpr int N = 2005;
constexpr int M = (1 << 13) + 5;
constexpr int mod = 998244353;
constexpr int block = 41;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void dec(int &x, int y)
{
    x -= y;
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
int prime[N], tot;
int mp[N];
bool vis[N];
inline void getprimes(int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            ++tot;
            mp[prime[tot] = i] = tot;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int f[303][M], h[M], dp[M];
int id[N], cnt;
vector<pair<int, int>> g[N];
inline void solve(int x, int y)
{
    int S = 0;
    for (int i = 1; i <= tot; ++i)
        if (x % prime[i] == 0)
        {
            S |= 1 << (i - 1);
            do
                x /= prime[i];
            while (x % prime[i] == 0);
        }
    if (x == 43 * 43)
        g[43].emplace_back(S, y);
    else
        g[x].emplace_back(S, y);
}
int n, m, q, a[N], b[N];
bool exist[N];
inline void work()
{
    memset(exist, 0, sizeof(exist));
    int S = 0;
    read(m);
    for (int i = 0; i < (1 << tot); ++i)
        h[i] = dp[i];
    for (int i = 1; i <= m; ++i)
    {
        read(b[i]);
        if (b[i] <= block)
            S |= 1 << (mp[b[i]] - 1);
        else
            exist[b[i]] = true;
    }
    for (int i = 1; i <= 2000; ++i)
    {
        if (exist[i])
        {
            if (g[i].empty())
            {
                printf("0\n");
                return;
            }
            for (int j = 0; j < (1 << tot); ++j)
                h[j] = (int)((ll)h[j] * f[id[i]][j] % mod);
        }
    }
    for (int i = 0; i < tot; ++i)
        for (int j = 0; j < (1 << tot); ++j)
            if ((j >> i) & 1)
                dec(h[j], h[j ^ (1 << i)]);
    int res = 0;
    for (int T = S; T < (1 << tot); T = (T + 1) | S)
        add(res, h[T]);
    printf("%d\n", res);
}
signed main()
{
    getprimes(block);
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        ++a[x];
    }
    for (int i = 1; i <= 2000; ++i)
        if (a[i])
            solve(i, a[i]);
    for (int i = 0; i < (1 << tot); ++i)
        dp[i] = 1;
    for (int u = 1; u <= 2000; ++u)
    {
        if (g[u].empty())
            continue;
        id[u] = ++cnt;
        for (auto v : g[u])
            add(f[id[u]][v.first], v.second);
        for (int i = 0; i < tot; ++i)
            for (int j = 0; j < (1 << tot); ++j)
                if ((j >> i) & 1)
                    add(f[id[u]][j], f[id[u]][j ^ (1 << i)]);
        for (int i = 0; i < (1 << tot); ++i)
        {
            f[id[u]][i] = (int)quickpow(2, f[id[u]][i]);
            dp[i] = (int)((ll)dp[i] * f[id[u]][i] % mod);
            f[id[u]][i] = (int)((ll)quickpow(f[id[u]][i], mod - 2) * (f[id[u]][i] - 1) % mod);
        }
    }
    read(q);
    while (q--)
        work();
    return 0;
}