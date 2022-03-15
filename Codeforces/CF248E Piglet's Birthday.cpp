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
const int N = 1e5 + 5, M = 6 * N;
int n, q, a[N], b[N];
double dp[N][110], C[M][10], answer;
signed main()
{
    C[0][0] = 1;
    for (int i = 1; i <= 5e5 + 100; ++i)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i && j <= 5; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        b[i] = a[i];
        ++dp[i][a[i]];
        answer += dp[i][0];
    }
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        int u, v, w;
        read(u, v, w);
        answer -= dp[u][0];
        for (int j = 0; j <= a[u]; j++)
        {
            double ans = 0;
            for (int k = j; k <= min(j + w, b[u]); k++)
                ans += dp[u][k] * C[k][k - j] * C[b[u] - k][w - (k - j)];
            dp[u][j] = ans / C[b[u]][w];
        }
        answer += dp[u][0];
        b[u] -= w, b[v] += w;
        printf("%.9lf\n", answer);
    }
    return 0;
}