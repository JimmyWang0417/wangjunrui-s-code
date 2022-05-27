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
const int N = 225;
int n, m;
double p[N];
int d[N];
double power[N][N], dp[N][N];
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        read(n, m);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lf%d", &p[i], &d[i]);
            double res = (1 - p[i]);
            power[i][0] = 1;
            for (int j = 1; j <= m; ++j)
                power[i][j] = power[i][j - 1] * res;
        }
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            dp[i][0] = dp[i - 1][0] * power[i][m];
            for (int j = min(i, m); j >= 1; --j)
                dp[i][j] = dp[i - 1][j] * power[i][m - j] + dp[i - 1][j - 1] * (1 - power[i][m - j + 1]);
        }
        double ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            double res = 0;
            for (int j = 0; j < i && j < m; ++j)
                res += (1 - power[i][m - j]) * dp[i - 1][j];
            ans += res * d[i];
        }
        printf("%.10lf\n", ans);
    }
    return 0;
}