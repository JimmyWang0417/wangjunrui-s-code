/**
 *    unicode: UTF-8
 *    name:    CF940E Cashback
 *    author:  whitepaperdog
 *    created: 2022.07.30 周六 11:05:04 (Asia/Shanghai)
 **/
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#define ll long long
#define lll __int128
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
constexpr int N = 1e5 + 5;
int n, c, a[N];
ll dp[N];
int q[N], head = 1, tail = 0;
signed main()
{
    read(n, c);
    ll sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        dp[i] = dp[i - 1] + a[i];
        if (i > c)
            sum -= a[i - c];
        while (head <= tail && q[head] <= i - c)
            ++head;
        while (head <= tail && a[q[tail]] > a[i])
            --tail;
        q[++tail] = i;
        sum += a[i];
        if (i >= c)
            ckmin(dp[i], dp[i - c] + sum - a[q[head]]);
    }
    printf("%lld\n", dp[n]);
    return 0;
}