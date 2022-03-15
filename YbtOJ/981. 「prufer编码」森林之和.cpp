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
constexpr int N = 5e3 + 5;
int mod;
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
ll f[N], g[N], h[N], l[N];
int C[N][N];
ll answer[N];
inline void init(int n)
{
    for (int i = C[0][0] = 1; i <= n; ++i)
        for (int j = C[i][0] = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    f[0] = f[1] = 1;
    g[0] = g[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        f[i] = quickpow(i, i - 2);
        for (int j = 1; j <= i; ++j)
            (g[i] += C[i - 1][j - 1] * g[i - j] % mod * f[j]) %= mod;
        ll now = 1;
        for (int j = i - 1; j >= 1; --j)
        {
            (h[i] += C[i - 2][j - 1] * now % mod * j % mod * j) %= mod;
            (now *= i - 1) %= mod;
        }
        for (int j = 1; j <= i; ++j)
            (l[i] += C[i - 1][j - 1] * g[i - j] % mod * h[j]) %= mod;
        answer[i] = l[i] * i % mod;
        // printf("%lld\n", h[i]);
    }
}
signed main()
{
    freopen("forest.in", "r", stdin);
    freopen("forest.out", "w", stdout);
    int T;
    read(T, mod);
    init(5e3);
    while (T--)
    {
        int x;
        read(x);
        printf("%lld\n", answer[x]);
    }
    return 0;
}