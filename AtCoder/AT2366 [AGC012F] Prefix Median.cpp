#include <algorithm>
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
constexpr int N = 55;
constexpr int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, a[N * 2];
int dp[N][N * 2][N * 2];
signed main()
{
    read(n);
    for (int i = 1; i < 2 * n; ++i)
        read(a[i]);
    sort(a + 1, a + 2 * n);
    dp[n][1][0] = 1;
    for (int i = n - 1; i >= 1; --i)
    {
        int pl = (a[i] != a[i + 1]), pr = (a[n + n - i] != a[n + n - i - 1]);
        for (int j = 0; j < 2 * n; ++j)
            for (int k = 0; j + k < 2 * n; ++k)
                if (dp[i + 1][j][k])
                {
                    for (int l = 1; l <= j + pl; ++l)
                        add(dp[i][j + pl - (l - 1)][k + pr + (l > 1)], dp[i + 1][j][k]);
                    for (int r = 1; r <= k + pr; ++r)
                        add(dp[i][j + pl + 1][k + pr - r], dp[i + 1][j][k]);
                }
    }
    int res = 0;
    for (int j = 0; j < 2 * n; ++j)
        for (int k = 0; j + k < 2 * n; ++k)
            add(res, dp[1][j][k]);
    printf("%d\n", res);
    return 0;
}