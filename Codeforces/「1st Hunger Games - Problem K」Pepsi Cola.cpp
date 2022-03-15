// Problem: K. Pepsi Cola
// Contest: Codeforces - The 1st Hunger Games
// URL: https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/K
// Memory Limit: 256 MB
// Time Limit: 1376 ms

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
constexpr int N = (1 << 17) + 5;
constexpr int m = 1 << 17;
constexpr int mod = 1e9 + 7;
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
int n, dp[N];
int power[N];
inline void FWT()
{
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                add(dp[i + j + k], dp[j + k]);
}
inline void UFWT()
{
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                dec(dp[i + j + k], dp[j + k]);
}
signed main()
{
    read(n);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power[i] = power[i - 1];
        add(power[i], power[i - 1]);
        int x;
        read(x);
        ++dp[x];
    }
    FWT();
    for (int i = 0; i < m; ++i)
        dp[i] = power[dp[i]];
    UFWT();
    ll ans = 0;
    for (int i = 0; i < m; ++i)
        (ans += (ll)i * i % mod * i % mod * dp[i]) %= mod;
    printf("%lld\n", ans);
    return 0;
}