/**
 *    unicode: UTF-8
 *    name:    P2059 [JLOI2013] 卡牌游戏
 *    author:  whitepaperdog
 *    created: 2022.07.31 周日 11:06:51 (Asia/Shanghai)
 **/
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
constexpr int N = 505;
int n, m, a[N];
double dp[N][N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
        read(a[i]);
    dp[1][0] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j < i; ++j)
        {
            for (int k = 1; k <= m; ++k)
            {
                int u = (a[k] - 1) % i;
                if (u == j)
                    continue;
                if (j > u)
                    dp[i][j] += dp[i - 1][j - u - 1];
                else
                    dp[i][j] += dp[i - 1][(i - 1) - (u - j)];
            }
            dp[i][j] /= m;
        }
    for (int i = 0; i < n; ++i)
        printf("%.2lf%% ", dp[n][i] * 100);
    putchar('\n');
    return 0;
}