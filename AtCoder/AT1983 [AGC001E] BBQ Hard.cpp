#include <bits/stdc++.h>
#define ll long long
#define lll __int128
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
constexpr int N = 4005, M = 2e5 + 5;
constexpr int mod = 1e9 + 7;
constexpr int inv2 = (mod + 1) / 2;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void dec(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int dp[N][N];
int C[N * 2][N];
int n, a[M], b[M];
signed main()
{
    for (int i = C[0][0] = 1; i <= 8000; ++i)
        for (int j = C[i][0] = 1; j <= i && j <= 4000; ++j)
        {
            C[i][j] = C[i - 1][j];
            add(C[i][j], C[i - 1][j - 1]);
        }
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i], b[i]);
        ++dp[2000 - a[i]][2000 - b[i]];
    }
    for (int i = 0; i <= 4000; ++i)
        for (int j = 0; j <= 4000; ++j)
        {
            add(dp[i][j], dp[i - 1][j]);
            add(dp[i][j], dp[i][j - 1]);
        }
    int answer = 0;
    for (int i = 1; i <= n; ++i)
    {
        add(answer, dp[a[i] + 2000][b[i] + 2000]);
        dec(answer, C[(a[i] + b[i]) * 2][b[i] * 2]);
    }
    printf("%lld\n", ((ll)answer * inv2 % mod));
    return 0;
}