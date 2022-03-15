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
const int N = 1e5 + 5;
int n, m, a[N];
int sum[N];
ll dp[N];
int f[N];
ll g[N];
int q[N];
inline void check(ll mid)
{
    int head = 1, tail = 0;
    q[++tail] = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (head < tail && (g[q[head + 1]] - g[q[head]]) < 2ll * (sum[i] + 1) * (sum[q[head + 1]] - sum[q[head]]))
            ++head;
        dp[i] = dp[q[head]] + (ll)(sum[i] - sum[q[head]] + 1) * (sum[i] - sum[q[head]] + 1) + mid;
        f[i] = f[q[head]] + 1;
        g[i] = dp[i] + (ll)sum[i] * sum[i];
        while (head < tail && (g[q[tail]] - g[q[tail - 1]]) * (sum[i] - sum[q[tail]]) > (g[i] - g[q[tail]]) * (sum[q[tail]] - sum[q[tail - 1]]))
            --tail;
        q[++tail] = i;
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    ll l = 0, r = 1e18, ans = 0;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        check(mid);
        if (f[n] <= m)
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    check(ans);
    printf("%lld\n", dp[n] - m * ans);
    return 0;
}