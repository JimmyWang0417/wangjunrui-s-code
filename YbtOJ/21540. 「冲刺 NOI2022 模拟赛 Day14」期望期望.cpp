#include <algorithm>
#include <cmath>
#include <cstdio>
#define ll long long
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
constexpr int N = 105;
int n, m, X, Y;
double a[N][N][N * 2], dp[N * 2][N * 2];
double answer[N];
inline void work()
{
    for (int i = 0; i < n + m - 1; ++i)
    {
        int where = i;
        for (int j = i + 1; j < n + m - 1; ++j)
            if (fabs(dp[j][i]) > fabs(dp[where][i]))
                where = j;
        if (where != i)
            swap(dp[where], dp[i]);
        for (int j = i + 1; j < n + m - 1; ++j)
        {
            double d = dp[j][i] / dp[i][i];
            for (int k = i; k <= n + m - 1; ++k)
                dp[j][k] -= d * dp[i][k];
        }
    }
    for (int i = n + m - 2; i >= 0; --i)
    {
        answer[i] = dp[i][n + m - 1];
        for (int j = i + 1; j < n + m - 1; ++j)
            answer[i] -= dp[i][j] * answer[j];
        answer[i] /= dp[i][i];
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("expect.in","r",stdin);
    freopen("expect.out","w",stdout);
#endif
    read(n, m, X, Y);
    for (int i = 0; i < n; ++i)
        a[i][m - 1][i] = 1;
    for (int i = 0; i < m - 1; ++i)
        a[n - 1][i][i + n] = 1;
    for (int i = n - 2; i >= 0; --i)
        for (int j = n - 2; j >= 0; --j)
        {
            if (i == X && j == Y)
                continue;
            for (int k = 0; k <= n + m - 1; ++k)
                a[i][j][k] = (a[i + 1][j][k] + a[i][j + 1][k]) / 2;
            ++a[i][j][n + m - 1];
        }
    for (int i = 0, j = m - 1; i < n; ++i)
    {
        dp[i][i] = 1;
        if (i == X && j == Y)
            continue;
        for (int k = 0; k < n + m - 1; ++k)
            dp[i][k] -= (a[(i + 1) % n][j][k] + a[i][(j + 1) % m][k]) / 2;
        dp[i][n + m - 1] = (a[(i + 1) % n][j][n + m - 1] + a[i][(j + 1) % m][n + m - 1]) / 2 + 1;
    }
    for (int i = n - 1, j = 0; j < m - 1; ++j)
    {
        dp[j + n][j + n] = 1;
        if (i == X && j == Y)
            continue;
        for (int k = 0; k < n + m - 1; ++k)
            dp[j + n][k] -= (a[(i + 1) % n][j][k] + a[i][(j + 1) % m][k]) / 2;
        dp[j + n][n + m - 1] = (a[(i + 1) % n][j][n + m - 1] + a[i][(j + 1) % m][n + m - 1]) / 2 + 1;
    }
    work();
    double res = a[0][0][n + m - 1];
    for (int i = 0; i < n + m - 1; ++i)
        res += answer[i] * a[0][0][i];
    printf("%lf\n", res);
    return 0;
}
