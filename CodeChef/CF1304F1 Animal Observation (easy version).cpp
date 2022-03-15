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
const int N = 56, M = 4e4 + 5;
int n, m, k;
int a[N][M];
int sum[N][M];
int dp[N][M];
int q[M], g[M];
signed main()
{
    read(n, m, k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            read(a[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m * 2; ++j)
            sum[i][j] = sum[i][j - 1] + a[i][j];
    for (int i = 1; i <= m; ++i)
        dp[1][i] = sum[1][i + k - 1] - sum[1][i - 1] + sum[2][i + k - 1] - sum[2][i - 1];
    for (int i = 2; i <= n; ++i)
    {
        int maxx = 0;
        int head = 1, tail = 0;
        for (int j = 1; j <= m; ++j)
        {
            while (head <= tail && g[tail] < dp[i - 1][j] - sum[i][j + k - 1])
                --tail;
            ++tail;
            q[tail] = j, g[tail] = dp[i - 1][j] - sum[i][j + k - 1];
            while (head <= tail && q[head] <= j - k)
            {
                ckmax(maxx, dp[i - 1][q[head]]);
                ++head;
            }
            dp[i][j] = max(maxx + sum[i][j + k - 1] - sum[i][j - 1], g[head] + sum[i][j + k - 1]);
        }
        head = 1, tail = 0;
        maxx = 0;
        for (int j = m; j >= 1; --j)
        {
            while (head <= tail && g[tail] < dp[i - 1][j] + sum[i][j - 1])
                --tail;
            ++tail;
            q[tail] = j, g[tail] = dp[i - 1][j] + sum[i][j - 1];
            while (head <= tail && q[head] >= j + k)
            {
                ckmax(maxx, dp[i - 1][q[head]]);
                ++head;
            }
            ckmax(dp[i][j], max(maxx + sum[i][j + k - 1] - sum[i][j - 1], g[head] - sum[i][j - 1]));
            dp[i][j] += sum[i + 1][j + k - 1] - sum[i + 1][j - 1];
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i)
        ckmax(ans, dp[n][i]);
    printf("%d\n", ans);
    return 0;
}