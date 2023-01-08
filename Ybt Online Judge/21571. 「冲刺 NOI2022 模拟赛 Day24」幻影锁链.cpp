#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 505, M = N * 3;
constexpr int mod = 998244353;
int n;
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
ll g[N][N];
inline ll solve()
{
    bool flag = false;
    for (int i = 1; i <= n; ++i)
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
            flag ^= 1;
        }
        ll inv = quickpow(g[i][i]);
        for (int j = i + 1; j <= n; ++j)
        {
            ll d = g[j][i] * inv % mod;
            for (int k = 1; k <= n; ++k)
                (g[j][k] -= d * g[i][k]) %= mod;
        }
    }
    ll answer = 1;
    for (int i = 1; i <= n; ++i)
        (answer *= g[i][i]) %= mod;
    return flag ? -answer : answer;
}
int a[M][M];
ll b[M][M];
ll dp[M][M];
inline ll calc(int x, int y)
{
    return (x ^ y) * quickpow((ll)x * y % mod) % mod;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
#endif
    read(n);
    ll res = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= 2 * i; ++j)
        {
            read(a[i][n - i + j]);
            (res *= a[i][n - i + j]) %= mod;
        }
    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= 2 * i; ++j)
        {
            read(a[2 * n - i + 1][n - i + j]);
            (res *= a[2 * n - i + 1][n - i + j]) %= mod;
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= 2 * i; ++j)
            b[i][n - i + j] = calc(a[i - 1][n - i + j], a[i][n - i + j]);
    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= 2 * i; ++j)
            b[2 * n - i + 1][n - i + j] = calc(a[2 * n - i][n - i + j], a[2 * n - i + 1][n - i + j]);
    for (int i = 1; i <= n; ++i)
    {
        memset(dp, 0, sizeof(dp));
        dp[0][i] = 1;
        for (int j = 0; j < 2 * n; ++j)
            for (int k = 1; k <= 2 * n; ++k)
                if (dp[j][k])
                {
                    if (a[2 * n - k + 1][n - i + j + 1] && a[2 * n - k + 1][n - i + j + 2])
                        (dp[j + 2][k] += dp[j][k]) %= mod;
                    (dp[j + 1][k + 1] += dp[j][k] * b[2 * n - k + 1][n - i + j + 1]) %= mod;
                    if (k >= 2)
                        (dp[j + 1][k - 1] += dp[j][k] * b[2 * n - k + 2][n - i + j + 1]) %= mod;
                }
        for (int j = 1; j <= n; ++j)
            g[i][j] = dp[i + j][j];
    }
    printf("%lld\n", (res * solve() % mod + mod) % mod);
    return 0;
}