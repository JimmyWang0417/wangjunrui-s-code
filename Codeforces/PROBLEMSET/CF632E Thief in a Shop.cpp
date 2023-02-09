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
int n, m, a[N];
int dp[N * N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    sort(a + 1, a + 1 + n);
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 2; i <= n; ++i)
    {
        int b = a[i] - a[1];
        for (int j = b; j <= 1e6; ++j)
            dp[j] = min(dp[j], dp[j - b] + 1);
    }
    for (int i = 0; i <= 1e6; ++i)
        if (dp[i] <= m)
            printf("%d ", i + m * a[1]);
    return 0;
}