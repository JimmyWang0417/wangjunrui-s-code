/**
 *    unicode: UTF-8
 *    name:    AT3950 [AGC022E] Median Replace
 *    author:  whitepaperdog
 *    created: 2022.07.12 周二 21:07:14 (Asia/Shanghai)
 **/
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
    bool dp = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            dp = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar();
    }
    if (dp)
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
constexpr int N = 3e5 + 5;
constexpr int mod = 1e9 + 7;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n;
int dp[N][3][3];
char str[N];
signed main()
{
    scanf("%s", str);
    n = (int)strlen(str);
    dp[0][0][0] = 1;
    for (int i = 0; str[i]; ++i)
    {
        if (str[i] != '1')
        {
            for (int a = 0; a <= 2; ++a)
            {
                add(dp[i + 1][a][1], dp[i][a][0]);
                add(dp[i + 1][a][2], dp[i][a][1]);
                add(dp[i + 1][a][1], dp[i][a][2]);
            }
        }
        if (str[i] != '0')
        {
            for (int a = 0; a <= 2; ++a)
            {
                add(dp[i + 1][a][0], dp[i][a][1]);
                add(dp[i + 1][a][1], dp[i][a][2]);
            }
            add(dp[i + 1][1][0], dp[i][0][0]);
            add(dp[i + 1][2][0], dp[i][1][0]);
            add(dp[i + 1][2][0], dp[i][2][0]);
        }
    }
    int res = 0;
    for (int a = 0; a <= 2; ++a)
        for (int b = 0; b <= a; ++b)
            add(res, dp[n][a][b]);
    printf("%d\n", res);
    return 0;
}