/**
 *    unicode: UTF-8
 *    name:    P6563 [SBCOI2020] 一直在你身旁
 *    author:  wangjunrui
 *    created: 2022.07.30 周六 09:17:16 (Asia/Shanghai)
 **/
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
constexpr int N = 7105;
int n, a[N];
ll dp[N][N];
int q[N], head, tail;
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)
            read(a[i]);
        for (int j = 2; j <= n; ++j)
        {
            head = 1, tail = 0;
            q[++tail] = j - 1;
            dp[j - 1][j] = a[j - 1];
            for (int i = j - 2, l = j; i; --i)
            {
                while (dp[i][l - 1] > dp[l][j] && l > i)
                    --l;
                while (head <= tail && l <= q[head])
                    ++head;
                dp[i][j] = a[l] + dp[i][l];
                if (head <= tail)
                    dp[i][j] = min(dp[i][j], dp[q[head] + 1][j] + a[q[head]]);
                while (head <= tail && a[q[tail]] + dp[q[tail] + 1][j] >= a[i] + dp[i + 1][j])
                    --tail;
                q[++tail] = i;
            }
        }
        printf("%lld\n", dp[1][n]);
    }
    return 0;
}