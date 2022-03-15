// Problem: B. Name That Tune
// Contest: Codeforces - Codeforces Round #284 (Div. 1)
// URL: https://codeforces.com/problemset/problem/498/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
const int N = 5005;
int n, m;
double dp[N][N];
signed main()
{
    read(n, m);
    dp[0][0] = 1;
    double answer = 0;
    for (int i = 1; i <= n; ++i)
    {
        int x, t;
        read(x, t);
        double p = x / 100.0, d = pow(1 - p, t), dd = pow(1 - p, t - 1), now = 0;
        for (int j = 1; j <= m; ++j)
        {
            if (j > t)
                now -= dp[i - 1][j - t - 1] * dd;
            now = now * (1 - p) + p * dp[i - 1][j - 1];
            if (j >= t)
                now += dp[i - 1][j - t] * d;
            dp[i][j] = now;
            answer += dp[i][j];
        }
    }
    printf("%lf\n", answer);
    return 0;
}