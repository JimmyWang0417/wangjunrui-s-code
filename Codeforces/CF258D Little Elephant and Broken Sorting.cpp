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
constexpr int N = 1005;
int n, m, a[N];
double dp[N][N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        for (int j = 1; j < i; ++j)
            if (a[i] < a[j])
                dp[i][j] = 1;
            else
                dp[j][i] = 1;
    }
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        for (int j = 1; j <= n; ++j)
        {
            dp[x][j] = dp[y][j] = 0.5 * (dp[x][j] + dp[y][j]);
            dp[j][x] = dp[j][y] = 1.0 - dp[x][j];
        }
        dp[x][y] = dp[y][x] = 0.5;
    }
    double res = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            res += dp[i][j];
    printf("%lf\n", res);
    return 0;
}