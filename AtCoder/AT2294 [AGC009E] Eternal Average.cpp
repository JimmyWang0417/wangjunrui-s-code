#include <cstdio>
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
constexpr int N = 2e3 + 5;
constexpr int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, k;
int dp[N * 2][N][2];
signed main()
{
    read(n, m, k);
    int limit = (n + m - 1) / (k - 1);
    dp[0][0][0] = 1;
    int res = 0;
    for (int i = 1; i <= limit; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            dp[i][j][0] = dp[i - 1][j][0];
            add(dp[i][j][0], dp[i - 1][j][1]);
            for (int x = 1; x < k && x <= j; x++)
            {
                add(dp[i][j][1], dp[i - 1][j - x][1]);
                add(dp[i][j][1], dp[i - 1][j - x][0]);
            }
        }
        for (int j = 0; j <= n; ++j)
            if (j % (k - 1) == n % (k - 1) && ((k - 1) * i + 1 - j) <= m &&
                ((k - 1) * i + 1 - j) % (k - 1) == m % (k - 1))
                add(res, dp[i][j][1]);
    }
    printf("%d\n", res);
    return 0;
}