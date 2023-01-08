#include <cstdio>
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
constexpr int N = 1e7 + 5;
constexpr int mod = 1e9 + 7;
inline int gcd(int n, int m)
{
    if (m == 0)
        return n;
    return gcd(m, n % m);
}
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
ll fac[N], ifac[N];
inline ll C(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
#define calc(n, m) C((n)-1, (m)-1)
int prime[N], tot;
int phi[N], minn[N];
bool vis[N];
inline void init(int n)
{
    phi[1] = 1;
    minn[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            phi[i] = i - 1;
            minn[i] = i;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            minn[i * prime[j]] = prime[j];
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
}
int p[N], q[N], cnt;
ll answer;
int n, m;
inline void dfs(int u, int val)
{
    if (u > cnt)
    {
        (answer += phi[val] * calc(n / val, m / val)) %= mod;
        return;
    }
    for (int i = 0; i <= q[u]; ++i)
    {
        dfs(u + 1, val);
        val *= p[u];
    }
}
int knhnmsl;
inline void work()
{
    read(n, m);
    int lim = (n - 1) / 2;
    answer = -m * calc(n - lim, m) % mod;
    cnt = 0;
    int d = gcd(n, m);
    while (d != 1)
    {
        ++cnt;
        p[cnt] = minn[d];
        q[cnt] = 0;
        while (p[cnt] == minn[d])
        {
            ++q[cnt];
            d /= minn[d];
        }
    }
    dfs(1, 1);
    if (m & 1)
    {
        if (n & 1)
            (answer += m * (calc((n + 1) / 2, (m + 1) / 2) - calc((n + 1) / 2 - (lim + 1) / 2, (m + 1) / 2))) %= mod;
        else
            (answer += m * (calc(n / 2, (m + 1) / 2) - calc(n / 2 - lim / 2, (m + 1) / 2))) %= mod;
    }
    else
    {
        ll val = calc((n + 1) / 2, m / 2 + 1);
        if (n & 1)
        {
            (val -= calc((n + 1) / 2 - lim / 2, m / 2 + 1)) %= mod;
            (val -= calc((n + 1) / 2 - (lim + 1) / 2, m / 2 + 1)) %= mod;
            (val += val) %= mod;
        }
        else
        {
            (val -= 2 * calc(n / 2 - lim / 2, m / 2 + 1) % mod) %= mod;
            (val += calc(n / 2 + 1, m / 2 + 1)) %= mod;
            (val -= 2 * calc(n / 2 - (lim + 1) / 2 + 1, m / 2 + 1) % mod) %= mod;
            (answer += (m / 2) * calc(n / 2, m / 2)) %= mod;
        }
        (answer += val * (m / 2)) %= mod;
    }
    knhnmsl ^= (int)((answer * quickpow(2 * m, mod - 2) % mod + mod) % mod);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("poly.in", "r", stdin);
    freopen("poly.out", "w", stdout);
#endif
    init(1e7);
    int T;
    read(T);
    while (T--)
        work();
    printf("%d\n", knhnmsl);
    return 0;
}
