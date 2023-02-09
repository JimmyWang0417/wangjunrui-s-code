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
const int N = 2e5 + 5, M = 1e7 + 5, K = 25;
int n, m, a[N];
int dp[N][K];
int L[N][K];
int cnt[M];
inline void work()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        int res = 1;
        for (int j = 2; j * j <= a[i]; ++j)
            if (a[i] % j == 0)
            {
                int nmsl = 0;
                while (a[i] % j == 0)
                {
                    a[i] /= j;
                    ++nmsl;
                }
                if (nmsl & 1)
                    res *= j;
            }
        a[i] *= res;
    }
    for (int limit = 0; limit <= m; ++limit)
    {
        int res = 0;
        for (int l = 1, r = 1; r <= n; ++r)
        {
            if (cnt[a[r]])
                ++res;
            ++cnt[a[r]];
            while (res > limit)
            {
                --cnt[a[l]];
                if (cnt[a[l]])
                    --res;
                ++l;
            }
            L[r][limit] = l;
        }
        for (int i = 1; i <= n; ++i)
            cnt[a[i]] = 0;
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
        {
            dp[i][j] = INT_MAX;
            for (int k = 0; k <= j; ++k)
                ckmin(dp[i][j], dp[L[i][k] - 1][j - k] + 1);
        }
    printf("%d\n", dp[n][m]);
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}