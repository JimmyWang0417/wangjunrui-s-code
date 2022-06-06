#include <bits/stdc++.h>
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
constexpr int N = 2e5 + 5;
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
int n, a, b;
vector<int> g[N];
int fa[N], sze[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
ll fac[N], ifac[N];
signed main()
{
    read(n, a, b);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        read(x, y);
        g[x].push_back(y);
    }
    int fi = 0x7fffffff, se = 0x7fffffff, pos = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (g[i].empty())
            continue;
        sort(g[i].begin(), g[i].end());
        if (g[i].front() < fi)
        {
            pos = i;
            se = fi;
            fi = g[i].front();
        }
        else if (g[i].front() < se)
            se = g[i].front();
    }
    for (int i = 1; i <= n; ++i)
    {
        if (g[i].empty())
            continue;
        sze[i] = 1;
        int limit = (int)max(a - g[i].front(), b - (i == pos ? se : fi));
        for (int j = 1; j < (int)g[i].size() && g[i][j] <= limit; ++j)
            ++sze[i];
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    ll answer = 1;
    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (g[i].empty())
            continue;
        if (pos == i)
        {
            (answer *= ifac[sze[i]]) %= mod;
            sum += sze[i];
        }
        else if (fi + g[i].front() <= b)
        {
            (answer *= ifac[sze[i]]) %= mod;
            sum += sze[i];
        }
    }
    printf("%lld\n", answer * fac[sum] % mod);
    return 0;
}