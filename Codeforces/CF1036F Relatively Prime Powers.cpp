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
const int N = 105;
int prime[N], tot, mul[N];
bool vis[N];
inline void getprimes(int n)
{
    mul[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            mul[i] = -1;
            prime[++tot] = i;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            else
                mul[i * prime[j]] = -mul[i];
        }
    }
}
inline long double quickpow(long double a, ll b)
{
    long double res = 1;
    while (b)
    {
        if (b & 1)
            res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
inline void work()
{
    ll n;
    read(n);
    ll res = 0;
    for (int i = 1; i <= 60; ++i)
    {
        ll now = (ll)pow((long double)n, (long double)1 / i) + 5;
        while (quickpow(now, i) > n)
            --now;
        res += mul[i] * (now - 1);
    }
    printf("%lld\n", res);
}
signed main()
{
    getprimes(100);
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}