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
const int N = 105, M = (1 << 15) + 5;
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
int k, n, a[N], b[N];
double dp[N][M];
signed main()
{
    read(k, n);
    for (int i = 0; i < n; ++i)
    {
        read(b[i]);
        int x;
        while (read(x), x)
            a[i] |= 1 << (x - 1);
    }
    for (int i = 1; i <= k; ++i)
    {
        for (int S = (1 << n) - 1; S >= 0; --S)
        {
            for (int j = 0; j < n; ++j)
            {
                double res = dp[i - 1][S];
                if ((S & a[j]) == a[j])
                    ckmax(res, dp[i - 1][S | (1 << j)] + b[j]);
                dp[i][S] += res / n;
            }
        }
    }
    printf("%lf\n", dp[k][0]);
    return 0;
}