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
const int N = 2e3 + 5;
int n, m;
bool h[N], l[N];
double dp[N][N];
ll inv[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        h[x] = true, l[y] = true;
    }
    int cnth = n, cntl = n;
    for (int i = 1; i <= n; ++i)
        cnth -= h[i];
    for (int i = 1; i <= n; ++i)
        cntl -= l[i];
    for (int i = 1; i <= n; ++i)
        dp[0][i] = dp[i][0] = dp[i - 1][0] + (double)n / i;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (n * n + i * j * dp[i - 1][j - 1] + (n - i) * j * dp[i][j - 1] + i * (n - j) * dp[i - 1][j]) / (n * n - (n - i) * (n - j));
    printf("%lf\n", dp[cnth][cntl]);
    return 0;
}