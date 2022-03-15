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
const int N = 5e5 + 5;
int n, a[N];
int l[N], r[N];
int cnt[N];
int dp[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (!l[a[i]])
            l[a[i]] = i;
        r[a[i]] = i;
    }
    for (int i = n; i >= 1; --i)
    {
        dp[i] = dp[i + 1];
        ++cnt[a[i]];
        if (l[a[i]] < i)
            ckmax(dp[i], cnt[a[i]]);
        else
            ckmax(dp[i], dp[r[a[i]] + 1] + cnt[a[i]]);
    }
    printf("%d\n", n - dp[1]);
    return 0;
}