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
const int N = 105;
int q, n;
double dp[N][N];
signed main()
{
    read(q, n);
    if (q == 1)
    {
        double res = 0;
        for (int i = 2; i <= n; ++i)
            res += 2.0 / i;
        printf("%lf\n", res);
    }
    else
    {
        for (int i = 1; i <= n; ++i)
            dp[i][0] = 1.0;
        for (int i = 2; i <= n; ++i)
            for (int j = 1; j < i; ++j)
            {
                for (int k = 1; k < i; ++k)
                    dp[i][j] += dp[k][j - 1] + dp[i - k][j - 1] - dp[k][j - 1] * dp[i - k][j - 1];
                dp[i][j] /= (i - 1);
            }
        double res = 0;
        for (int i = 1; i < n; ++i)
            res += dp[n][i];
        printf("%lf\n", res);
    }
    return 0;
}