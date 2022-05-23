#include <bits/stdc++.h>
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
constexpr int N = 505;
int n, mod;
ll dp[2][N][N];
signed main()
{
    read(n, mod);
    int now = 1, las = 0;
    for (int i = 1; i < n; ++i)
        dp[now][1][i] = i;
    for (int i = 2; i <= n; ++i)
    {
        swap(now, las);
        memset(dp[now], 0, sizeof(dp[0]));
        ll res = 0;
        for (int j = 1; j < i; ++j)
            (res += dp[las][j][1] * j) %= mod;
        printf("%lld\n", (res + mod) % mod);
        for (int j = 1; j < i; ++j)
            for (int k = 1; k <= n; ++k)
            {
                const ll ad = dp[las][j][k] * j % mod;
                (dp[now][j][k] -= 2 * ad * k) %= mod;
                (dp[now][j + 1][k] += ad * k) %= mod;
                (dp[now][j][k - 1] += ad * (k - 1)) %= mod;
            }
    }
    return 0;
}