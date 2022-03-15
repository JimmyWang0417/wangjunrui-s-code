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
using namespace std;
const int N = 1005 + 5;
ll dp[N][N][2];
int n, x0;
ll sumy, sum[N];
struct node
{
    int x, y, v;
} a[N];
#define calc(x, y) (sum[y] - sum[(x)-1])
inline void init()
{
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + a[i].v;
        sumy += a[i].y;
    }
    memset(dp, ~0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i)
        dp[i][i][0] = dp[i][i][1] = sumy - sum[n] * abs(x0 - a[i].x);
    for (int len = 2; len <= n; ++len)
    {
        for (int l = 1, r; l + len - 1 <= n; ++l)
        {
            r = l + len - 1;
            dp[l][r][0] = max(dp[l + 1][r][0] - (calc(1, l) + calc(r + 1, n)) * abs(a[l + 1].x - a[l].x),
                              dp[l + 1][r][1] - (calc(1, l) + calc(r + 1, n)) * abs(a[r].x - a[l].x));
            dp[l][r][1] = max(dp[l][r - 1][0] - (calc(1, l - 1) + calc(r, n)) * (a[r].x - a[l].x),
                              dp[l][r - 1][1] - (calc(1, l - 1) + calc(r, n)) * (a[r].x - a[r - 1].x));
        }
    }
}
signed main()
{
    read(n, x0);
    for (int i = 1; i <= n; ++i)
        read(a[i].x);
    for (int i = 1; i <= n; ++i)
        read(a[i].y);
    for (int i = 1; i <= n; ++i)
        read(a[i].v);
    sort(a + 1, a + 1 + n, [](const node &lhs, const node &rhs)
         { return lhs.x < rhs.x; });
    init();
    printf("%.3lf\n",(double)max(dp[1][n][0], dp[1][n][1])/1000.0);
    return 0;
}