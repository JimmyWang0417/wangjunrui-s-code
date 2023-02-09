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
const int N = 505;
int n, m;
ll dp[N][N];
signed main()
{
    read(n, m);
    int sum = 0;
    memset(dp, ~0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        read(a, b);
        for (int j = 0; j < m; ++j)
            if (dp[i][j] >= 0)
                for (int k = 0; k < m && k <= a; ++k)
                {
                    int preb = (sum - j + m) % m, addb = ((a + b) % m + m - k) % m;
                    if (addb > b)
                        continue;
                    int d = (a + b - k - addb) / m;
                    if (j + k >= m)
                        ++d;
                    if (preb + addb >= m)
                        ++d;
                    ckmax(dp[i + 1][(j + k) % m], dp[i][j] + d);
                }
        (sum += a + b) %= m;
    }
    ll ans = -1e18;
    for (int i = 0; i < m; ++i)
        ckmax(ans, dp[n][i]);
    printf("%lld\n", ans);
    return 0;
}