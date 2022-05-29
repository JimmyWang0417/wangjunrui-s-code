#include <algorithm>
#include <climits>
#include <cstdio>
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
int n, m, T;
int a[N];
ll dp[N];
ll g[N];
int q[N], head, tail;
signed main()
{
    read(n, m, T);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    ll minn = 1e15;
    q[head = tail = 1] = 0;
    for (int i = 1, j = 0; i <= n; ++i)
    {
        while (head <= tail && 2 * (a[i] - a[q[head] + 1]) > T)
            ++head;
        while (2 * (a[i] - a[j + 1]) > T)
        {
            ckmin(minn, dp[j] - a[j] - 2 * a[j + 1]);
            ++j;
        }
        dp[i] = 3ll * a[i] + minn;
        if (head <= tail)
            ckmin(dp[i], a[i] + g[head] + T);
        ll now = dp[i] - a[i];
        while (head <= tail && g[tail] > now)
            --tail;
        ++tail;
        q[tail] = i;
        g[tail] = now;
    }
    printf("%lld\n", dp[n] + m - a[n]);
    return 0;
}