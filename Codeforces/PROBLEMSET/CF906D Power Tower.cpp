#include <bits/stdc++.h>
#define int long long
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
constexpr int N = 1e5 + 5;
int n, m;
inline int phi(int x)
{
    int res = x;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
        {
            do
                x /= i;
            while (x % i == 0);
            res = res / i * (i - 1);
        }
    if (x > 1)
        res = res / x * (x - 1);
    return res;
}
inline int quickpow(int a, int b, int mod)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = res * a;
            if (res >= mod)
                res = res % mod + mod;
        }
        a = a * a;
        if (a >= mod)
            a = a % mod + mod;
        b >>= 1;
    }
    return res;
}
map<int, int> mp;
int a[N];
inline int dfs(int pos, int ed, int p)
{
    if (pos == ed + 1 || p == 1)
        return 1;
    return quickpow(a[pos], dfs(pos + 1, ed, mp[p]), p);
}
signed main()
{
    read(n, m);
    int x = m;
    while (x != 1)
        x = mp[x] = phi(x);
    mp[x] = 1;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    int q;
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        int l, r;
        read(l, r);
        printf("%lld\n", dfs(l, r, m) % m);
    }
    return 0;
}