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
const int N = 2e5 + 5;
int n, m;
ll suma[N];
double sumb[N], sumc[N];
double X[N], Y[N];
double dp[55][N];
int q[N];
inline double getslope(int x, int y)
{
    return (Y[x] - Y[y]) / (X[x] - X[y]);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        suma[i] = suma[i - 1] + x;
        sumb[i] = sumb[i - 1] + 1.0 / x;
        sumc[i] = sumc[i - 1] + (double)suma[i] / x;
    }
    for (int i = 1; i <= n; ++i)
        dp[0][i] = 1e18;
    dp[0][0] = 0;
    for (int j = 1; j <= m; ++j)
    {
        int head = 1, tail = 0;
        q[++tail] = 0;
        X[0] = 0, Y[0] = dp[j - 1][0] + (double)suma[0] * sumb[0] - sumc[0];
        for (int i = 1; i <= n; ++i)
        {
            while (head < tail && getslope(q[head + 1], q[head]) <= sumb[i])
                ++head;
            dp[j][i] = dp[j - 1][q[head]] + sumc[i] - sumc[q[head]] - (double)suma[q[head]] * (sumb[i] - sumb[q[head]]);
            X[i] = (double)suma[i], Y[i] = dp[j - 1][i] + (double)suma[i] * sumb[i] - sumc[i];
            while (head < tail && getslope(q[tail - 1], q[tail]) >= getslope(q[tail], i))
                --tail;
            q[++tail] = i;
        }
    }
    printf("%.10lf\n", dp[m][n]);
    return 0;
}