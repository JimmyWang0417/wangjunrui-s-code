#include <cstdio>
#include <cstring>
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
constexpr int N = 1005, M = 10005;
constexpr int mod = 998244353;
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
int n, k, m;
int dp[M][15];
int inv[M];
signed main()
{
    read(n, k, m);
    inv[1] = 1;
    for (int i = 2; i <= m; ++i)
        inv[i] = (int)((ll)(mod - mod / i) * inv[mod % i] % mod);
    k = n + 1 - k;
    for (int i = 1; i <= k; ++i)
        dp[0][i] = -1;
    for (int kase = 1; kase <= n; ++kase)
    {
        int w;
        read(w);
        for (int i = m; i >= w; --i)
        {
            for (int j = k; j >= 1; --j)
            {
                dec(dp[i][j], dp[i - w][j]);
                add(dp[i][j], dp[i - w][j - 1]);
            }
        }
    }
    ll answer = 0;
    for (int i = 1; i <= m; ++i)
        (answer += (ll)dp[i][k] * inv[i]) %= mod;
    printf("%lld\n", answer * m % mod);
    return 0;
}