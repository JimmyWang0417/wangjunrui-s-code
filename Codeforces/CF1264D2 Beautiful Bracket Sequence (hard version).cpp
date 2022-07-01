/**
 *    unicode: UTF-8
 *    name:    CF1588F Jumping Through the Array
 *    author:  wangjunrui
 *    created: 2022.07.01 周五 19:13:20 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
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
int n;
char str[N];
int pre[N], sum[N];
ll fac[N], ifac[N];
inline ll C(int x, int y)
{
    if (x < y || y < 0)
        return 0;
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
signed main()
{
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] + (str[i] == '(');
        sum[i] = sum[i - 1] + (str[i] == '?');
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    ll answer = 0;
    for (int i = pre[n]; i <= sum[n] + pre[n]; ++i)
    {
        int pos = n - i;
        (answer += C(sum[n], i - pre[n]) * pre[pos] + C(sum[n] - 1, i - pre[n] - 1) * sum[pos]) %= mod;
    }
    printf("%lld\n", answer);
    return 0;
}