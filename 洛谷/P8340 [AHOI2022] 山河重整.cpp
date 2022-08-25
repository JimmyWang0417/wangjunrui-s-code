/**
 *    unicode: UTF-8
 *    name:    P8340 [AHOI2022] 山河重整
 *    author:  wangjunrui
 *    created: 2022.08.17 周三 00:48:55 (Asia/Shanghai)
 **/
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
constexpr int N = 5e5 + 5;
int n, mod;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
template <typename T>
inline void del(T &x, T y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int f[N], g[N];
inline void solve(int m)
{
    if (m <= 1)
        return;
    solve(m / 2);
    for (int i = m; i >= 1; --i)
    {
        if ((ll)i * (i + 1) / 2 > m)
            continue;
        for (int j = n; j >= i; --j)
            g[j] = g[j - i];
        for (int j = 0; j + (j + 2) * i <= m; j++)
            add(g[j + (j + 2) * i], f[j]);
        for (int j = i; j <= n; ++j)
            add(g[j], g[j - i]);
    }
    for (int i = m / 2 + 1; i <= m; ++i)
        del(f[i], g[i]);
    fill(g, g + m + 1, 0);
}
int power[N];
signed main()
{
    read(n, mod);
    for (int i = n; i >= 1; --i)
    {
        if ((ll)i * (i + 1) / 2 > n)
            continue;
        for (int j = n; j >= i; --j)
            f[j] = f[j - i];
        add(f[i], 1);
        for (int j = i; j <= n; ++j)
            add(f[j], f[j - i]);
    }
    f[0] = 1;
    solve(n);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power[i] = power[i - 1];
        add(power[i], power[i - 1]);
    }
    ll res = power[n];
    for (int i = 0; i < n; ++i)
        (res -= (ll)f[i] * power[n - i - 1]) %= mod;
    printf("%lld\n", (res + mod) % mod);
    return 0;
}