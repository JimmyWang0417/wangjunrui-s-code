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
constexpr int N = 2e3 + 5;
constexpr int mod = 924844033;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m;
int a[2 * N];
int dp[2 * N][N][2];
ll f[N], g[N], fac[N];
signed main()
{
    read(n, m);
    for (int i = 0; i < n; ++i)
    {
        int x = (i + m) % (2 * m);
        if (i >= m)
            ++a[x];
        if (i + m < n)
            ++a[x];
    }
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
        {
            dp[i][j][0] = dp[i - 1][j][0];
            add(dp[i][j][0], dp[i - 1][j][1]);
            if (j)
                dp[i][j][1] = dp[i - 1][j - 1][0];
        }
    f[0] = 1;
    for (int i = 0, sum = 0; i < 2 * m; ++i)
    {
        memcpy(g, f, sizeof(f));
        memset(f, 0, sizeof(f));
        for (int j = 0; j <= sum; ++j)
            for (int k = 0; k <= a[i]; ++k)
                (f[j + k] += g[j] * (dp[a[i]][k][0] + dp[a[i]][k][1])) %= mod;
        sum += a[i];
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ll res = 0;
    for (int i = 0; i <= n; ++i)
        if (i & 1)
            (res -= f[i] * fac[n - i]) %= mod;
        else
            (res += f[i] * fac[n - i]) %= mod;
    printf("%lld\n", (res + mod) % mod);
    return 0;
}