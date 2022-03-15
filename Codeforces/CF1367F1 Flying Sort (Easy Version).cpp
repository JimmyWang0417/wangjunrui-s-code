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
const int N = 2e5 + 5;
int n, a[N];
int p[N], tot;
int dp[N][3];
int L[N], R[N], cnt[N], mp[N];
inline void work()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[i] = a[i];
    }
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
        if (!L[a[i]])
            L[a[i]] = i;
        R[a[i]] = i;
        ++cnt[a[i]];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        dp[i][0] = dp[mp[a[i]]][0] + 1;
        dp[i][1] = max(dp[mp[a[i]]][1], max(dp[mp[a[i] - 1]][0], dp[mp[a[i] - 1]][2])) + 1;
        if (i == R[a[i]])
            dp[i][2] = dp[L[a[i]]][1] + cnt[a[i]] - 1;
        ckmax(ans, max(dp[i][0], max(dp[i][1], dp[i][2])));
        mp[a[i]] = i;
    }
    printf("%d\n", n - ans);
    memset(dp, 0, sizeof(dp));
    memset(mp, 0, sizeof(mp));
    memset(cnt, 0, sizeof(cnt));
    memset(L, 0, sizeof(L));
    memset(R, 0, sizeof(R));
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}