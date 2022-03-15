#include <bits/stdc++.h>
#include <bits/extc++.h>
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
const int N = 1005;
const int mod = 998244353;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, k, a[N];
int dp[N][N];
signed main()
{
    read(n, k);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    sort(a + 1, a + 1 + n);
    int s = (a[n] - a[1]) / (k - 1);
    a[0] = INT_MIN;
    int res = 0;
    for (int minn = 1; minn <= s; ++minn)
    {
        int now = 0;
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            while (a[now] <= a[i] - minn)
                ++now;
            --now;
            dp[i][0] = dp[i - 1][0];
            for (int j = 1; j <= k; ++j)
                dp[i][j] = (dp[i - 1][j] + dp[now][j - 1]) % mod;
        }
        add(res, dp[n][k]);
    }
    printf("%d\n", res);
    return 0;
}