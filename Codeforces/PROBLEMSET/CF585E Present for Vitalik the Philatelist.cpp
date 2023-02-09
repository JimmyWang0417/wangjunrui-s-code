/**
 *    unicode: UTF-8
 *    name:    CF585E Present for Vitalik the Philatelist
 *    author:  whitepaperdog
 *    created: 2022.07.03 周日 23:41:13 (Asia/Shanghai)
 **/
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
constexpr int N = 5e5 + 5, M = 1e7 + 5;
constexpr int mod = 1e9 + 7;
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
int n, m, a[N], b[M], c[M];
int prime[M], tot;
int mul[M];
bool vis[M];
inline void getprimes(int limit)
{
    mul[1] = 1;
    for (int i = 2; i <= limit; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            mul[i] = -1;
        }
        for (int j = 1; j <= tot && i * prime[j] <= limit; ++j)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            else
                mul[i * prime[j]] = -mul[i];
        }
    }
}
int power[N];
signed main()
{
    read(n);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        ++b[a[i]];
        ckmax(m, a[i]);
        power[i] = power[i - 1];
        add(power[i], power[i - 1]);
    }
    getprimes(m);
    for (int i = 1; i <= tot; ++i)
        for (int j = m / prime[i]; j >= 1; --j)
            add(b[j], b[prime[i] * j]);
    for (int i = 1; i <= m; ++i)
    {
        if (mul[i] == 1)
            c[i] = b[i];
        else if (mul[i] == -1)
            c[i] = (mod - b[i]) % mod;
    }
    for (int i = 1; i <= tot; ++i)
        for (int j = 1; prime[i] * j <= m; ++j)
            add(c[prime[i] * j], c[j]);
    for (int i = 1; i <= m; ++i)
        b[i] = power[b[i]] - 1;
    for (int i = tot; i >= 1; --i)
        for (int j = 1; prime[i] * j <= m; ++j)
            del(b[j], b[prime[i] * j]);
    ll res = 0;
    for (int i = 2; i <= m; ++i)
        (res += (ll)b[i] * c[i]) %= mod;
    printf("%lld\n", res);
    return 0;
}