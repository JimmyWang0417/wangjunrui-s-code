/**
 *    unicode: UTF-8
 *    name:    P5415 [YNOI2019] 游戏
 *    author:  wangjunrui
 *    created: 2022.07.29 周五 16:14:12 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cmath>
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
constexpr int N = 115;
double dp[N][N];
inline void solve(int limit)
{
    for (int i = 1; i <= limit; ++i)
    {
        int where = i;
        for (int j = i + 1; j <= limit; ++j)
            if (fabs(dp[where][i]) < fabs(dp[j][i]))
                where = j;
        if (where != i)
            swap(dp[where], dp[i]);
        for (int j = i + 1; j <= limit; ++j)
        {
            double times = dp[j][i] / dp[i][i];
            for (int k = i; k <= limit + 1; ++k)
                dp[j][k] -= dp[i][k] * times;
        }
    }

    for (int i = limit; i >= 1; --i)
    {
        for (int j = i + 1; j <= limit; ++j)
        {
            dp[i][limit + 1] -= dp[i][j] * dp[j][limit + 1];
            dp[i][j] = 0;
        }
        dp[i][limit + 1] /= dp[i][i];
    }
}
signed main()
{
    int T = 1;
    read(T);
    while (T--)
    {
        int n, m, k;
        read(n, m, k);
        auto calc = [n](int x, int y)
        { return x + y * n; };
        memset(dp, 0, sizeof(dp));
        dp[calc(1, m)][calc(1, m)] = 1, dp[calc(1, m)][calc(n, m) + 1] = 1;
        for (int i = 2; i <= n; ++i)
            dp[calc(i, m)][calc(i, m)] = 1;
        for (int i = 0; i < m; ++i)
        {
            dp[calc(1, i)][calc(1, i)] += -1;
            dp[calc(1, i)][calc(1, i + 1)] += 0.25;
            dp[calc(1, i)][calc(n - 2, 1)] += 0.75;

            dp[calc(2, i)][calc(2, i)] += -1;
            dp[calc(2, i)][calc(1, 1)] += 0.25;
            dp[calc(2, i)][calc(n - 2, i + 1)] += 0.25;
            dp[calc(2, i)][calc(n - 1, 1)] += 0.5;

            dp[calc(3, i)][calc(3, i)] += -1;
            dp[calc(3, i)][calc(1, 1)] += 0.25;
            dp[calc(3, i)][calc(n - 1, i + 1)] += 0.25;
            dp[calc(3, i)][calc(n - 1, 1)] += 0.25;
            dp[calc(3, i)][calc(n, 1)] += 0.25;

            dp[calc(4, i)][calc(4, i)] += -1;
            dp[calc(4, i)][calc(1, 1)] += 0.25;
            dp[calc(4, i)][calc(n, i + 1)] += 0.25;
            dp[calc(4, i)][calc(n, 1)] += 0.5;

            for (int j = 5; j <= n; ++j)
            {
                dp[calc(j, i)][calc(j, i)] += -1;
                dp[calc(j, i)][calc(j - 3, i + 1)] += 0.25;
                dp[calc(j, i)][calc(j - 3, 1)] += 0.75;
            }
        }
        solve(n * (m + 1));
        printf("%lf\n", fabs(dp[calc(k, 0)][calc(n, m) + 1]) < 1e-7 ? 0 : dp[calc(k, 0)][calc(n, m) + 1]);
    }
    return 0;
}