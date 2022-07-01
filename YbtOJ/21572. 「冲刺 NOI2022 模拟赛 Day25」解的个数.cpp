#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
using namespace std;
const int N = 3e6 + 5;
const int mod = 1e9 + 7;
inline ll quickpow(ll a, int b)
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
int n, m;
ll fac[N], inv[N];
inline ll C(int x, int y)
{
    return fac[x] * inv[x - y] % mod * inv[y] % mod;
}
inline ll B(int x, int y);
inline ll A(int x, int y)
{
    if (x < 0 || y < 0)
        return 0;
    return (C(x + y, x) - B(y + 1, x - 1) + mod) % mod;
}
inline ll B(int x, int y)
{
    if (x < 0 || y < 0)
        return 0;
    return (C(x + y, x) - A(y - (m + 2), x + (m + 2)) + mod) % mod;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("x.in","r",stdin);
    freopen("x.out","w",stdout);
#endif
    read(n, m);
    int maxx = max(n, m) * 3 + 1;
    fac[0] = 1;
    for (int i = 1; i <= maxx; ++i)
        fac[i] = fac[i - 1] * i % mod;
    inv[maxx] = quickpow(fac[maxx], mod - 2);
    for (int i = maxx - 1; i >= 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    printf("%lld\n", (C(2 * n + m + 1, n) - A(n - 1, n + m + 2) - B(n + m + 2, n - 1) + mod + mod) % mod);
    return 0;
}
