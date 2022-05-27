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
const int N = 25, M = (1 << 20) + 5;
int n, m, a[N][N], b[N][N], c[N][N];
char str[N][N];
int dp[M];
signed main()
{
    read(n, m);
    for (int i = 0; i < n; ++i)
        scanf("%s", str[i]);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            read(a[i][j]);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int sum = 0;
            int maxx = 0;
            for (int k = 0; k < n; ++k)
                if (str[i][j] == str[k][j])
                {
                    sum += a[k][j];
                    ckmax(maxx, a[k][j]);
                    b[i][j] |= (1 << k);
                }
            c[i][j] = sum - maxx;
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    int T = (1 << n) - 1;
    for (int i = 0; i < T; ++i)
    {
        int j = 0;
        for (; (i >> j) & 1; ++j)
            ;
        for (int k = 0; k < m; ++k)
        {
            ckmin(dp[i | (1 << j)], dp[i] + a[j][k]);
            ckmin(dp[i | b[j][k]], dp[i] + c[j][k]);
        }
    }
    printf("%d\n", dp[T]);
    return 0;
}