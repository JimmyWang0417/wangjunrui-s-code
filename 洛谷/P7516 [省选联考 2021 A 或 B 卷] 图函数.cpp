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
constexpr int N = 1e3 + 5, M = 2e5 + 5;
int n, m;
int dp[N][N];
int answer[M];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        dp[u][v] = i;
    }
    answer[m + 1] = n;
    for (int k = n; k >= 1; --k)
    {
        for (int i = k + 1; i <= n; ++i)
            ++answer[min(dp[k][i], dp[i][k])];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                ckmax(dp[i][j], min(dp[i][k], dp[k][j]));
    }
    for (int i = m; i >= 1; --i)
        answer[i] += answer[i + 1];
    for (int i = 1; i <= m + 1; ++i)
        printf("%d ", answer[i]);
    putchar('\n');
    return 0;
}