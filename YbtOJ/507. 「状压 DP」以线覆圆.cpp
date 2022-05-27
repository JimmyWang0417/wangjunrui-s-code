// Problem: F - Arcs on a Circle
// Contest: AtCoder - AtCoder Grand Contest 020
// URL: https://atcoder.jp/contests/agc020/tasks/agc020_f
// Memory Limit: 512 MB
// Time Limit: 5000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
const int N = 10, M = 55;
int n, m, a[N];
int p[N];
ll dp[500][(1 << 6) + 5];
signed main()
{
    freopen("circle.in", "r", stdin);
    freopen("circle.out", "w", stdout);
    read(n, m);
    for (int i = 0; i < n; ++i)
    {
        read(a[i]);
        p[i] = i;
    }
    sort(a, a + n, greater<int>());
    ll ans = 0;
    int cnt = 0;
    do
    {
        memset(dp, 0, sizeof(dp));
        dp[a[0] * n][1] = 1;
        for (int i = 1; i < n * m; ++i)
            for (int j = i; j <= n * m; ++j)
            {
                int t = i % n;
                for (int k = 0; k < (1 << n); k++)
                    if (~k >> t & 1)
                        dp[min(n * m, max(j, i + a[p[t]] * n))][k | (1 << t)] += dp[j][k];
            }
        ans += dp[n * m][(1 << n) - 1];
        ++cnt;
    } while (next_permutation(p + 1, p + n));
    double res = (double)ans / cnt;
    for (int i = 1; i < n; ++i)
        res /= m;
    printf("%.12lf\n", res);
    return 0;
}
