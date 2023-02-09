#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 205, M = 1005;
const int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, a[N];
int dp[N][N][M];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    sort(a + 1, a + 1 + n);
    dp[1][1][0] = dp[1][0][0] = 1;
    for (int i = 2; i <= n; ++i)
    {
        int d = a[i] - a[i - 1];
        for (int j = 0; j <= i; ++j)
        {
            for (int k = 0; k <= m; ++k)
            {
                if (j * d <= k)
                    add(dp[i][j][k], (int)((ll)dp[i - 1][j][k - j * d] * (j + 1) % mod));
                if (j && (j - 1) * d <= k)
                    add(dp[i][j][k], dp[i - 1][j - 1][k - (j - 1) * d]);
                if ((j + 1) * d <= k)
                    add(dp[i][j][k], (int)((ll)dp[i - 1][j + 1][k - (j + 1) * d] * (j + 1) % mod));
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i <= m; ++i)
        (ans += dp[n][0][i]) %= mod;
    printf("%lld\n", ans);
    return 0;
}