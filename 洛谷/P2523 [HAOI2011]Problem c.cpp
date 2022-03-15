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
const int N = 305;
int n, m, mod, C[N][N], suf[N];
ll dp[N][N];
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void work()
{
    read(n, m, mod);
    for (int i = C[0][0] = 1; i <= n; ++i)
    {
        for (int j = C[i][0] = 1; j <= i; ++j)
        {
            C[i][j] = C[i - 1][j];
            add(C[i][j], C[i - 1][j - 1]);
        }
    }
    memset(suf, 0, sizeof(suf));
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        ++suf[y];
    }
    for (int i = n; i >= 1; --i)
    {
        suf[i] += suf[i + 1];
        if (suf[i] > n - i + 1)
        {
            printf("NO\n");
            return;
        }
    }
    memset(dp, 0, sizeof(dp));
    dp[n + 1][0] = 1;
    for (int i = n; i >= 1; --i)
        for (int j = n - suf[i] - i + 1; j >= 0; --j)
        {
            dp[i][j] = 0;
            for (int k = 0; k <= j; ++k)
                (dp[i][j] += dp[i + 1][j - k] * C[j][k]) %= mod;
        }
    printf("YES %lld\n", dp[1][n - m]);
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}