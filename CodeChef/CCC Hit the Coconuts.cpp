#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 2e3 + 5;
int n, m, a[N];

int dp[N][N];
int X[N], Y[N];

int q[N];
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        read(n, m);
        for (int i = 1; i <= n; ++i)
            read(a[i]);
        sort(a + 1, a + 1 + n);
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i <= n; ++i)
            dp[i][0] = 0;
        for (int j = 1; j <= m; ++j)
        {
            int r;
            q[r = 1] = 0, X[0] = a[1], Y[0] = dp[0][j - 1];
            for (int i = 1; i <= n; ++i)
            {
                while (r > 1 && -(X[q[r]] - X[q[r - 1]]) * i < (Y[q[r]] - Y[q[r - 1]]))
                    --r;
                dp[i][j] = dp[q[r]][j - 1] + a[q[r] + 1] * (i - q[r]);
                X[i] = a[i + 1], Y[i] = dp[i][j - 1] - i * a[i + 1];
                while (r > 1 && (ll)(X[q[r - 1]] - X[q[r]]) * (Y[i] - Y[q[r]]) > (ll)(X[i] - X[q[r]]) * (Y[q[r - 1]] - Y[q[r]]))
                    --r;
                q[++r] = i;
            }
        }
        printf("%d\n", dp[n][m]);
    }
    return 0;
}