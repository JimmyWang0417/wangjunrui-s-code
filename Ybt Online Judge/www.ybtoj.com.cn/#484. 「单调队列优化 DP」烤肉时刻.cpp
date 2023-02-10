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
constexpr int K = 105, N = 1e5 + 5;
int n, k;
int dp[K][N];
pair<int, int> a[K];
int q[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("barbecue.in", "r", stdin);
    freopen("barbecue.out", "w", stdout);
#endif
    read(n, k);
    for (int i = 1; i <= k; ++i)
        read(a[i].first, a[i].second);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= k; ++i)
    {
        memcpy(dp[i], dp[i - 1], sizeof(dp[i]));
        int len = a[i].second - a[i].first;
        int l = 1, r = 0;
        for (int j = 0; j <= n; ++j)
        {
            while (l <= r && q[l] < j - len)
                ++l;
            while (l <= r && dp[i - 1][q[r]] > dp[i - 1][j])
                --r;
            q[++r] = j;
            ckmin(dp[i][j], dp[i - 1][q[l]] + 2);
        }
        l = 1, r = 0;
        for (int j = 0; j <= a[i].second && j <= n; ++j)
        {
            while (l <= r && q[l] < j - len)
                ++l;
            while (l <= r && dp[i - 1][q[r]] > dp[i - 1][j])
                --r;
            q[++r] = j;
            ckmin(dp[i][a[i].second - j], dp[i - 1][q[l]] + 1);
        }
    }
    // for (int i = 1; i <= k; ++i)
    // {
    //     for (int j = 0; j <= n; ++j)
    //         printf("%d ", dp[i][j]);
    //     putchar('\n');
    // }
    if (dp[k][n] != 0x3f3f3f3f)
        printf("YES\n%d\n", dp[k][n]);
    else
        printf("NO\n");
    return 0;
}