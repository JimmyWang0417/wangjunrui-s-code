#include <cstdio>
#define int ll
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
constexpr int N = 1005;
int n, x, mod, m;
inline ll quickpow(ll a, int b)
{
    ll res = 1;
    a %= mod;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
int a[N];
ll b[N];
ll s2[N][N];
signed main()
{
    read(n, x, mod, m);
    for (int i = 0; i <= m; ++i)
        read(a[i]);
    s2[0][0] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= i; ++j)
            s2[i][j] = (s2[i - 1][j - 1] + s2[i - 1][j] * j) % mod;
    for (int i = 0; i <= m; ++i)
        for (int j = i; j <= m; ++j)
            (b[i] += s2[j][i] * a[j]) %= mod;
    ll answer = 0;
    for (int i = 0, now = 1; i <= m; ++i)
    {
        (answer += b[i] * now % mod * quickpow(x, i) % mod * quickpow(x + 1, n - i)) %= mod;
        (now *= (n - i)) %= mod;
    }
    printf("%lld\n", (answer + mod) % mod);
    return 0;
}