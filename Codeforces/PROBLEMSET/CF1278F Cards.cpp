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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 5005;
constexpr int mod = 998244353;
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
int n, m, k;
ll s2[N][N];
signed main()
{
    read(n, m, k);
    s2[0][0] = 1;
    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= i; ++j)
            s2[i][j] = (s2[i - 1][j - 1] + s2[i - 1][j] * j) % mod;
    ll p = quickpow(m), resn = 1, resp = 1, res = 0;
    for (int i = 0; i <= k; (resn *= (n - i)) %= mod, (resp *= p) %= mod, ++i)
        (res += s2[k][i] * resn % mod * resp) %= mod;
    printf("%lld\n", res);
    return 0;
}