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
const int N = 1005;
int n, m;
double dp[N][N], answer;
signed main()
{
    read(n, m);
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j)
        {
            double A = (double)(n - i) / (n + m - i - j), B = 1 - A;
            if ((i + j) % 3 == 0)
            {
                answer += dp[i][j] * A;
                dp[i][j + 1] += dp[i][j] * B;
            }
            else if ((i + j) % 3 == 1)
                dp[i][j + 1] += dp[i][j] * B;
            else
            {
                dp[i + 1][j] += dp[i][j] * A;
                dp[i][j + 1] += dp[i][j] * B;
            }
        }
    printf("%.9lf\n", answer);
    return 0;
}