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
constexpr int N = 15, mod = 2004;

int n, l, r, a[N];
ll fac = 1, sum = 0;

inline ll C(int x, int y)
{
    ll M = mod * fac, ans = 1;
    for (int i = y - x + 1; i <= y; i++)
        ans = (ans * i) % M;
    return (ans / fac) % mod;
}

void dfs(int step, int val, int key, int lim)
{
    if (key > lim)
        return;
    if (step == n + 1)
    {
        sum += 1ll * val * C(n, n + lim - key) % mod;
        sum %= mod;
        return;
    }
    dfs(step + 1, val, key, lim), dfs(step + 1, -val, key + a[step] + 1, lim);
}

inline ll solve(int lim)
{
    sum = 0;
    dfs(1, 1, 0, lim);
    return (sum % mod + mod) % mod;
}

signed main()
{
    read(n, l, r);
    for (int i = 1; i <= n; i++)
        read(a[i]), fac = fac * i;
    printf("%lld\n", ((solve(r) - solve(l - 1)) % mod + mod) % mod);
    return 0;
}