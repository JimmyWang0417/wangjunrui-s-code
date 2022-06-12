#include <bits/stdc++.h>
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
constexpr int N = 305;
int n, m;
int dp[N][N][N];
char str[N];
signed main()
{
    scanf("%s", str + 1);
    read(m);
    n = (int)strlen(str + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            dp[i][i][j] = 1;
    for (int j = 0; j <= n; ++j)
        for (int len = 2; len <= n; ++len)
            for (int l = 1; l + len - 1 <= n; ++l)
            {
                int r = l + len - 1;
                dp[l][r][j] = max(dp[l + 1][r][j], dp[l][r - 1][j]);
                if (str[l] == str[r])
                    ckmax(dp[l][r][j], dp[l + 1][r - 1][j] + 2);
                else if (j)
                    ckmax(dp[l][r][j], dp[l + 1][r - 1][j - 1] + 2);
            }
    printf("%d\n", dp[1][n][m]);
    return 0;
}