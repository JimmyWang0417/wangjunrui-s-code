// Problem: E. Ehab and the Expected GCD Problem
// Contest: Codeforces - Codeforces Round #563 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1174/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
int n, m;
int dp[N][25][2];
inline int calc0(int x)
{
    return n >> x;
}
inline int calc1(int x)
{
    return (n >> x) / 3;
}
signed main()
{
    read(n);
    while ((1 << m) <= n)
        ++m;
    --m;
    dp[1][m][0] = 1;
    if ((1 << (m - 1)) * 3 <= n)
        dp[1][m - 1][1] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
        {
            dp[i][j][0] = ((ll)dp[i - 1][j][0] * (calc0(j) - i + 1) + (ll)dp[i - 1][j + 1][0] * (calc0(j) - calc0(j + 1)) + (ll)dp[i - 1][j][1] * (calc0(j) - calc1(j))) % mod;
            dp[i][j][1] = ((ll)dp[i - 1][j][1] * (calc1(j) - i + 1) + (ll)dp[i - 1][j + 1][1] * (calc1(j) - calc1(j + 1))) % mod;
        }
    printf("%d\n", dp[n][0][0]);
    return 0;
}