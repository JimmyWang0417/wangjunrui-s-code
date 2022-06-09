#include <cstdio>
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
constexpr int mod = 1e9 + 7;
int n, m, a[15];
ll dp[(1 << 15) + 5];
signed main()
{
    read(n, m);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        read(u, v);
        --u, --v;
        a[u] |= 1 << v;
    }
    dp[0] = 1;
    for (int S = 0; S < (1 << n); ++S)
        if (dp[S])
        {
            int subS = ((1 << n) - 1) ^ S;
            for (int T = subS; T; T = (T - 1) & subS)
                if ((T & 3) == 0 || (T & 3) == 3)
                {
                    ll all = 1;
                    for (int i = 0; i < n; ++i)
                        if ((S >> i) & 1)
                            (all *= (1 << __builtin_popcount(a[i] & T)) - 1) %= mod;
                        else if ((T >> i) & 1)
                            (all *= 1 << __builtin_popcount(a[i] & S)) %= mod;
                    (dp[S | T] += all * dp[S]) %= mod;
                }
        }
    int res = 1;
    for (int i = 1; i <= m; ++i)
        (res *= 2) %= mod;
    printf("%lld\n", ((res - dp[(1 << n) - 1]) % mod + mod) % mod);
    return 0;
}
