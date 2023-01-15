/**
 *    unicode: UTF-8
 *    name:    P3800 Power收集
 *    author:  whitepaperdog
 *    created: 2022.07.30 周六 08:21:55 (Asia/Shanghai)
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
constexpr int N = 4005;
int n, m, k, T;
int a[N][N];
int dp[N][N];
int q[N], head, tail;
signed main()
{
    read(n, m, k, T);
    for (int i = 1; i <= k; ++i)
    {
        int x, y, t;
        read(x, y, t);
        a[x][y] = t;
    }
    for (int i = 1; i <= m; ++i)
        dp[1][i] = a[1][i];
    for (int i = 2; i <= n; ++i)
    {
        head = 1, tail = 0;
        for (int j = 1; j <= m; ++j)
        {
            while (head <= tail && q[head] < j - T)
                ++head;
            while (head <= tail && dp[i - 1][j] > dp[i - 1][q[tail]])
                --tail;
            q[++tail] = j;
            dp[i][j] = dp[i - 1][q[head]] + a[i][j];
        }
        head = 1, tail = 0;
        for (int j = m; j >= 1; --j)
        {
            while (head <= tail && q[head] > j + T)
                ++head;
            while (head <= tail && dp[i - 1][j] > dp[i - 1][q[tail]])
                --tail;
            q[++tail] = j;
            ckmax(dp[i][j], dp[i - 1][q[head]] + a[i][j]);
        }
    }
    int res = 0;
    for (int i = 1; i <= m; ++i)
        ckmax(res, dp[n][i]);
    printf("%d\n", res);
    return 0;
}