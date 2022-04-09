#include <algorithm>
#include <cstdio>
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
constexpr int N = (1 << 13) + 5, M = 505;
int n, m;
int a[N];
int popcount[N];
int Log[N];
ll dp[N][13][M];
signed main()
{
    read(n, m);
    int t = 0;
    for (int i = 0; i < n; ++i)
    {
        read(a[i]);
        if (a[i] > a[t])
            t = i;
    }
    for (int S = 1; S < (1 << n); ++S)
        popcount[S] = popcount[S ^ lowbit(S)] + 1;
    for (int i = 0; i < n; ++i)
        Log[1 << i] = i;
    for (int i = 0; i < n; ++i)
    {
        int nxt = n * (a[t] - a[i] + (t < i));
        if (nxt <= m)
            dp[1 << i][i][nxt] = 1;
    }
    for (int S = 0; S < (1 << n); ++S)
        for (int i = 0; i < n; ++i)
            if ((S >> i) & 1)
                for (int j = 0; j <= m; ++j)
                    if (dp[S][i][j])
                    {
                        for (int k = 0; k < n; ++k)
                        {
                            if ((S >> k) & 1)
                                continue;
                            int nxt = j + (n - popcount[S]) * max(a[i] - a[k] + (k > i), 0);
                            if (nxt <= m)
                                dp[S | (1 << k)][k][nxt] += dp[S][i][j];
                        }
                    }
    ll answer = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j)
            answer += dp[(1 << n) - 1][i][j];
    printf("%lld\n", answer);
    return 0;
}