#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = (1 << 21) + 5;
int n, m, a[N];
pair<int, int> dp[N];
signed main()
{
    read(n);
    int maxx = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        ckmax(maxx, a[i]);
    }
    m = 1;
    while (m <= maxx)
        m <<= 1;
    for (int i = n; i >= 1; --i)
    {
        if (dp[a[i]].first)
        {
            if (dp[a[i]].second)
                continue;
            dp[a[i]].second = i;
        }
        else
            dp[a[i]].first = i;
    }
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
            {
                if (dp[j + k].first < dp[i + j + k].first)
                {
                    dp[j + k].second = max(dp[j + k].first, dp[i + j + k].second);
                    dp[j + k].first = dp[i + j + k].first;
                }
                else if (dp[j + k].second < dp[i + j + k].first)
                    dp[j + k].second = dp[i + j + k].first;
            }
    int ans = 0;
    for (int i = n - 2; i >= 0; --i)
    {
        int res = 0, now = 0;
        for (int j = 21; j >= 0; --j)
            if ((a[i] >> j) & 1)
                res |= 1 << j;
            else
            {
                if (dp[now | 1 << j].second > i)
                {
                    now |= 1 << j;
                    res |= 1 << j;
                }
            }
        ckmax(ans, res);
    }
    printf("%d\n", ans);
    return 0;
}