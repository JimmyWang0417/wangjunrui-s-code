#include <algorithm>
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
constexpr int N = 2e6 + 5;
constexpr int mod = 1e9 + 7;
inline ll quickpow(ll a, int b = mod - 2)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
ll fac[N], ifac[N];
inline ll C(int x, int y)
{
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
inline ll calc(int x1, int y1, int x2, int y2)
{
    int x = x2 - x1, y = y2 - y1;
    return C(x + y, x);
}
ll answer;
int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
inline void solve(int a, int b, int c, int d, int val)
{
    ll res = 0;
    for (int i = x3; i <= x4; ++i)
    {
        (res -= calc(a, b, i, y3 - 1) * calc(i, y3, c, d) % mod * (i + y3)) %= mod;
        (res += calc(a, b, i, y4) * calc(i, y4 + 1, c, d) % mod * (i + y4 + 1)) %= mod;
    }
    for (int i = y3; i <= y4; ++i)
    {
        (res -= calc(a, b, x3 - 1, i) * calc(x3, i, c, d) % mod * (x3 + i)) %= mod;
        (res += calc(a, b, x4, i) * calc(x4 + 1, i, c, d) % mod * (x4 + i + 1)) %= mod;
    }
    (answer += res * val) %= mod;
}
signed main()
{
    read(x1, x2, x3, x4, x5, x6);
    read(y1, y2, y3, y4, y5, y6);
    fac[0] = 1;
    for (int i = 1; i <= x6 + y6; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[x6 + y6] = quickpow(fac[x6 + y6]);
    for (int i = x6 + y6; i >= 0; --i)
        ifac[i - 1] = ifac[i] * i % mod;

    solve(x1 - 1, y1 - 1, x5, y5, 1);
    solve(x1 - 1, y1 - 1, x5, y6 + 1, -1);
    solve(x1 - 1, y1 - 1, x6 + 1, y5, -1);
    solve(x1 - 1, y1 - 1, x6 + 1, y6 + 1, 1);

    solve(x1 - 1, y2, x5, y5, -1);
    solve(x1 - 1, y2, x5, y6 + 1, 1);
    solve(x1 - 1, y2, x6 + 1, y5, 1);
    solve(x1 - 1, y2, x6 + 1, y6 + 1, -1);

    solve(x2, y1 - 1, x5, y5, -1);
    solve(x2, y1 - 1, x5, y6 + 1, 1);
    solve(x2, y1 - 1, x6 + 1, y5, 1);
    solve(x2, y1 - 1, x6 + 1, y6 + 1, -1);

    solve(x2, y2, x5, y5, 1);
    solve(x2, y2, x5, y6 + 1, -1);
    solve(x2, y2, x6 + 1, y5, -1);
    solve(x2, y2, x6 + 1, y6 + 1, 1);

    printf("%lld\n", (answer + mod) % mod);
    return 0;
}
