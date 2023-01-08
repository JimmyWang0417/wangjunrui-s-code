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
constexpr int N = 2005;
int n, k, mod;
int C[N][N];
int w[N][N];
int power[N];
int dp[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("runaround.in", "r", stdin);
    freopen("runaround.out", "w", stdout);
#endif
    read(n, k, mod);
    for (int i = C[0][0] = 1; i <= n; ++i)
        for (int j = C[i][0] = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
        power[i] = (int)((ll)power[i - 1] * (k * 2) % mod);
    for (int i = 0; i * 2 <= n; ++i)
        w[1][i] = C[i * 2][i];
    for (int i = 2; i <= k; ++i)
        for (int j = 0; j <= n / 2; ++j)
            for (int l = 0; l <= j; ++l)
                w[i][j] = (int)((w[i][j] + (ll)w[i - 1][j - l] * w[1][l] % mod * C[j * 2][l * 2]) % mod);
    int answer = 0;
    for (int i = 0; i <= n; ++i)
    {
        dp[i] = power[i];
        for (int j = i - 2; j >= 0; j -= 2)
            dp[i] = (int)((dp[i] - (ll)dp[j] * w[k][(i - j) / 2]) % mod);
        answer = (int)((answer + (ll)dp[i] * power[n - i]) % mod);
    }
    printf("%d\n", (answer + mod) % mod);
    return 0;
}