// Problem: D. Steps to One
// Contest: Codeforces - Codeforces Round #548 (Div. 2)
// URL: http://codeforces.com/problemset/problem/1139/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
constexpr int N = 1e5 + 5;
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
int prime[N], tot;
int mul[N];
bool vis[N];
ll inv[N];
inline void getprime(int n)
{
    mul[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            mul[i] = -1;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                mul[i * prime[j]] = 0;
                break;
            }
            else
                mul[i * prime[j]] = -mul[i];
        }
    }
    for (int i = 2; i <= n; ++i)
        mul[i] += mul[i - 1];
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}
inline void work()
{
    ll ans = -1;
    int n;
    read(n);
    for (int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        (ans += (mul[r] - mul[l - 1]) * (inv[n - n / l] * n % mod - 1)) %= mod;
    }
    printf("%lld\n", (-ans + mod) % mod);
}
signed main()
{
    getprime(1e5);
    work();
    return 0;
}
