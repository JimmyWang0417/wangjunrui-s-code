// Problem: D. Broken robot
// Contest: Codeforces - Codeforces Beta Round #24
// URL: https://codeforces.com/problemset/problem/24/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int N = 1e3 + 5;
int n, m, x, y;
double dp[N][N], answer[N];
inline void solve()
{
    for (int i = 1; i < m; ++i)
    {
        double d = dp[i + 1][i] / dp[i][i];
        dp[i + 1][i] = 0;
        dp[i + 1][i + 1] -= d * dp[i][i + 1];
        dp[i + 1][m + 1] -= d * dp[i][m + 1];
    }
    answer[m] = dp[m][m + 1] / dp[m][m];
    for (int i = m - 1; i >= 1; --i)
        answer[i] = (dp[i][m + 1] - dp[i][i + 1] * answer[i + 1]) / dp[i][i];
}
signed main()
{
    read(n, m, x, y);
    n -= (x - 1);
    if (m == 1)
        printf("%d\n", 2 * (n - 1));
    else
    {
        for (int i = 1; i < n; ++i)
        {
            dp[1][1] = 2;
            dp[1][2] = -1;
            dp[1][m + 1] = 3 + answer[1];

            for (int j = 2; j < m; ++j)
            {
                dp[j][j - 1] = -1;
                dp[j][j] = 3;
                dp[j][j + 1] = -1;
                dp[j][m + 1] = 4 + answer[j];
            }

            dp[m][m - 1] = -1;
            dp[m][m] = 2;
            dp[m][m + 1] = 3 + answer[m];

            solve();
        }
        printf("%lf\n", answer[y]);
    }
    return 0;
}