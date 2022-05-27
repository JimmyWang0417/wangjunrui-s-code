#include <bits/stdc++.h>
#define int ll
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
constexpr int N = 33, M = 2e6 + 5;
constexpr int mod = 998244353;
int n, x, y, z, have[N];
int a[N], tot;
ll dp[23][M][2];
bool vis[23][M][2];
ll power[N], powerx[N][3], powery[50], powerz[50];
inline ll quickpow(ll a, ll b)
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
inline ll dfs(int pos, ll sum, bool need, bool limit)
{
    if (pos == -1)
        return need ? 0 : powery[__builtin_popcount(sum)];
    if (pos < 13 && !limit && vis[pos][sum][need])
        return dp[pos][sum][need];
    ll res = 0;
    int maxx = limit ? a[pos] : 2;
    for (int i = 0; i <= maxx; ++i)
        for (int j = 0; j < 2; ++j)
        {
            ll now = sum + power[pos] * i + (j << have[pos]);
            if ((now >= (1ll << have[pos + 1])) != need)
                continue;
            now &= (1ll << have[pos + 1]) - 1;
            (res += dfs(pos - 1, now & ((1ll << have[pos]) - 1), j, limit && i == maxx) *
                    powerx[pos][i] % mod * powery[__builtin_popcount(now >> have[pos])] % mod * powerz[i] % mod) %= mod;
        }
    if (pos < 13 && !limit)
    {
        dp[pos][sum][need] = res;
        vis[pos][sum][need] = true;
    }
    return res;
}
signed main()
{
    read(n, x, y, z);
    power[0] = 1;
    for (int i = 1; i <= 28; ++i)
        power[i] = power[i - 1] * 3;
    for (int i = 0; i <= 28; ++i)
    {
        powerx[i][0] = 1;
        powerx[i][1] = quickpow(x, power[i]);
        powerx[i][2] = powerx[i][1] * powerx[i][1] % mod;
    }
    powery[0] = powerz[0] = 1;
    for (int i = 1; i <= 44; ++i)
    {
        powery[i] = powery[i - 1] * y % mod;
        powerz[i] = powerz[i - 1] * z % mod;
    }
    have[0] = 0;
    for (int i = 1; i <= 28; ++i)
    {
        have[i] = have[i - 1];
        while ((1ll << have[i]) < power[i])
            ++have[i];
    }
    tot = -1;
    while (n)
    {
        a[++tot] = n % 3;
        n /= 3;
    }
    printf("%lld\n", (dfs(tot + 1, 0, 0, true) + mod - 1) % mod);
    return 0;
}