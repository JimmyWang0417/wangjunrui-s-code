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
const int N = (1 << 22) + 5;
int n, m, a[N];
int dp[N];
signed main()
{
    read(n);
    int maxx = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (!dp[a[i]])
            dp[a[i]] = a[i];
        ckmax(maxx, a[i]);
    }
    m = 1;
    while (m <= maxx)
        m <<= 1;
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                if (!dp[i + j + k])
                    dp[i + j + k] = dp[j + k];
    for (int i = 1; i <= n; ++i)
        dp[(m - 1) ^ a[i]] ? printf("%d ", dp[(m - 1) ^ a[i]]) : printf("-1 ");
    putchar('\n');
    return 0;
}