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
constexpr int N = 1e5 + 5;
constexpr int mod = 19491001;
constexpr int inv2 = (mod + 1) / 2;
constexpr int root5 = 5485845;
constexpr int invroot5 = 1097169;
inline ll quickpow(ll a, ll b)
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
signed main()
{
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
    ll n;
    read(n);
    ++n;
    printf("%lld\n", ((quickpow((ll)(1 + root5) * inv2 % mod, n) - quickpow((ll)(1 - root5) * inv2 % mod, n) + mod) % mod * invroot5 % mod + mod - 1) % mod);
    return 0;
}
