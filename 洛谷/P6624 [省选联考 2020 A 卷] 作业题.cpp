#include <algorithm>
#include <cstdio>
#include <cstring>
#define int ll
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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 35, M = 152501 + 5;
constexpr int mod = 998244353;
int prime[M], cnt;
int phi[M];
bool vis[M];
inline void getprime(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j])
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            else
                phi[i * prime[j]] = phi[i] * prime[j];
        }
    }
}
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
int n, m;
pair<ll, ll> g[N][N];
inline pair<ll, ll> operator*(const pair<ll, ll> &lhs, const pair<ll, ll> &rhs)
{
    return make_pair(lhs.first * rhs.first % mod, (lhs.first * rhs.second + lhs.second * rhs.first) % mod);
}
inline pair<ll, ll> operator/(const pair<ll, ll> &lhs, const pair<ll, ll> &rhs)
{
    return make_pair(lhs.first * quickpow(rhs.first) % mod,
                     (lhs.second * rhs.first - lhs.first * rhs.second) % mod * quickpow(rhs.first * rhs.first % mod) % mod);
}
inline void operator+=(pair<ll, ll> &lhs, const pair<ll, ll> rhs)
{
    (lhs.first += rhs.first) %= mod;
    (lhs.second += rhs.second) %= mod;
}
inline void operator-=(pair<ll, ll> &lhs, const pair<ll, ll> rhs)
{
    (lhs.first -= rhs.first) %= mod;
    (lhs.second -= rhs.second) %= mod;
}
inline pair<ll, ll> solve()
{
    bool flag = false;
    for (int i = 1; i < n; ++i)
    {
        int where = 0;
        for (int j = i; j < n; ++j)
            if (g[j][i].first || g[j][i].second)
            {
                where = j;
                break;
            }
        if (where != i)
        {
            swap(g[where], g[i]);
            flag ^= 1;
        }
        for (int j = i + 1; j < n; ++j)
        {
            pair<ll, ll> times = g[j][i] / g[i][i];
            for (int k = i; k < n; ++k)
                g[j][k] -= times * g[i][k];
        }
    }
    pair<ll, ll> answer = make_pair(1, 0);
    for (int i = 1; i < n; ++i)
        answer = answer * g[i][i];
    if (flag)
    {
        answer.first = -answer.first;
        answer.second = -answer.second;
    }
    return answer;
}
struct node
{
    int u, v, w;
} a[N * N];
int p[M], tot;
inline void init(int val)
{
    for (int i = 1; i * i <= val; ++i)
        if (val % i == 0)
        {
            p[++tot] = i;
            if (i * i != val)
                p[++tot] = val / i;
        }
}
signed main()
{
    getprime(M - 5);
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        read(a[i].u, a[i].v, a[i].w);
        init(a[i].w);
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    ll answer = 0;
    for (int kase = 1; kase <= tot; ++kase)
    {
        memset(g, 0, sizeof(g));
        int cnt = 0;
        for (int i = 1; i <= m; ++i)
        {
            int u = a[i].u, v = a[i].v, w = a[i].w;
            if (w % p[kase])
                continue;
            g[u][u] += make_pair(1, w);
            g[v][v] += make_pair(1, w);
            g[u][v] -= make_pair(1, w);
            g[v][u] -= make_pair(1, w);
            ++cnt;
        }
        if (cnt < n - 1)
            continue;
        (answer += phi[p[kase]] * solve().second) %= mod;
    }
    printf("%lld\n", (answer + mod) % mod);
    return 0;
}