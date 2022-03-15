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
const int mod = 998244353;
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
const int N = 2e5 + 5;
int n, m, d[N], sum[N];
inline ll getinv(int val)
{
    return quickpow(val, mod - 2);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(d[i]);
    sort(d + 1, d + 1 + n);
    for (int i = 1; i <= n; ++i)
        sum[i] = (sum[i - 1] + d[i]) % mod;
    while (m--)
    {
        int a, b;
        read(a, b);
        int pos = (int)(lower_bound(d + 1, d + 1 + n, b) - d - 1), cnt = n - pos;
        if (cnt < a)
            printf("0\n");
        else
        {
            ll ans = ((ll)(sum[n] - sum[pos]) * (cnt - a) % mod * getinv(cnt) % mod +
                      (ll)sum[pos] * (cnt + 1 - a) % mod * getinv(cnt + 1) % mod) %
                     mod;
            printf("%lld\n", (ans + mod) % mod);
        }
    }
    return 0;
}