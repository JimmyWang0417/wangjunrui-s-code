/**
 *    unicode: UTF-8
 *    name:    CF338D d Table
 *    author:  whitepaperdog
 *    created: 2022.06.29 周三 20:03:06
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
constexpr int N = 1e4 + 5;
inline void exgcd(ll a, ll b, ll &d, ll &x, ll &y)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b, d, y, x);
        y -= a / b * x;
    }
}
inline ll slowtimes(ll a, ll b, ll p)
{
    ll res = 0;
    while (b)
    {
        if (b & 1)
            (res += a) %= p;
        (a += a) %= p;
        b >>= 1;
    }
    return res;
}
inline ll __lcm(ll x, ll y)
{
    return x / __gcd(x, y) * y;
}
ll n, m;
int k;
ll a[N], b[N];
signed main()
{
    read(n, m, k);
    ll qwq = 1;
    for (int i = 1; i <= k; ++i)
    {
        read(a[i]);
        b[i] = ((1 - i) % a[i] + a[i]) % a[i];
        if ((qwq = __lcm(qwq, a[i])) > n)
        {
            printf("NO\n");
            return 0;
        }
    }
    ll lcm = a[1], sol = b[1];
    for (int i = 2; i <= k; ++i)
    {
        ll d, x, y;
        b[i] = (b[i] - sol % a[i] + a[i]) % a[i];
        exgcd(lcm, a[i], d, x, y);
        if (b[i] % d != 0)
        {
            printf("NO\n");
            return 0;
        }
        sol += slowtimes(x, (b[i] / d), a[i]) * lcm;
        lcm = lcm / d * a[i];
        sol = (sol % lcm + lcm) % lcm;
    }
    sol = (sol + lcm - 1) % lcm + 1;
    if (sol + k - 1 > m)
    {
        printf("NO\n");
        return 0;
    }
    for (int i = 1; i <= k; ++i)
    {
        if (__gcd(lcm, sol + i - 1) != a[i])
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}