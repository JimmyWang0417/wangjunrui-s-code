#include <algorithm>
#include <cstdio>
#include <vector>
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
constexpr int N = 5e5 + 5, mod = 1e9 + 7;
template <typename T>
inline T lcm(T x, T y)
{
    return x / __gcd(x, y) * y;
}
int n, m, a[N], b[N];
int prime[N], tot, minprime[N];
int p[N], qwq;
int cnt[N];
bool vis[N];
ll inv[N];
vector<pair<int, int>> g[N];
int maxx[N][3];
bool exist[N][3];
ll all;
inline void init(int limit)
{
    inv[1] = 1;
    for (int i = 2; i <= limit; ++i)
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    for (int i = 2; i <= limit; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            minprime[i] = i;
        }
        for (int j = 1; j <= tot && i * prime[j] <= limit; ++j)
        {
            vis[i * prime[j]] = true;
            minprime[i * prime[j]] = prime[j];
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= limit; ++i)
    {
        int x = i;
        while (x > 1)
        {
            int y = minprime[x], now = 1;
            while (x % y == 0)
            {
                x /= y;
                now *= y;
            }
            g[i].emplace_back(y, now);
        }
    }
}
inline void insert(int x)
{
    for (auto u : g[x])
    {
        if (maxx[u.first][0] < u.second)
        {
            maxx[u.first][2] = maxx[u.first][1];
            maxx[u.first][1] = maxx[u.first][0];
            maxx[u.first][0] = u.second;
        }
        else if (maxx[u.first][1] < u.second)
        {
            maxx[u.first][2] = maxx[u.first][1];
            maxx[u.first][1] = u.second;
        }
        else if (maxx[u.first][2] < u.second)
            maxx[u.first][2] = u.second;
    }
}
inline void add(int u)
{
    for (auto v : g[u])
    {
        for (int j = 0; j < 3; ++j)
            if (!exist[v.first][j])
            {
                (all *= inv[maxx[v.first][j]]) %= mod;
                break;
            }
        for (int j = 0; j < 3; ++j)
            if (exist[v.first][j] && maxx[v.first][j] == v.second)
            {
                exist[v.first][j] = false;
                break;
            }
        for (int j = 0; j < 3; ++j)
            if (!exist[v.first][j])
            {
                (all *= maxx[v.first][j]) %= mod;
                break;
            }
    }
}
inline void del(int u)
{
    for (auto v : g[u])
    {
        for (int j = 0; j < 3; ++j)
            if (!exist[v.first][j])
            {
                (all *= inv[maxx[v.first][j]]) %= mod;
                break;
            }
        for (int j = 0; j < 3; ++j)
            if (!exist[v.first][j] && maxx[v.first][j] == v.second)
            {
                exist[v.first][j] = true;
                break;
            }
        for (int j = 0; j < 3; ++j)
            if (!exist[v.first][j])
            {
                (all *= maxx[v.first][j]) %= mod;
                break;
            }
    }
}
inline ll calc(int u)
{
    ll res = all;
    for (auto v : g[u])
    {
        int las = 0;
        for (int j = 0; j < 3; ++j)
            if (!exist[v.first][j])
            {
                las = maxx[v.first][j];
                break;
            }
        (res *= max(v.second / las, 1)) %= mod;
    }
    return res;
}
inline void work()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    m = 0;
    fill(vis + 1, vis + 1 + n, false);
    for (int i = 1; i <= n; ++i)
    {
        if (vis[i])
            continue;
        int size = 0;
        for (int j = i; !vis[j]; j = a[j], ++size)
            vis[j] = true;
        ++m;
        p[m] = b[m] = size;
    }
    sort(p + 1, p + 1 + m);
    qwq = (int)(unique(p + 1, p + 1 + m) - p - 1);
    fill(cnt + 1, cnt + 1 + m, 0);
    for (int i = 1; i <= m; ++i)
        ++cnt[lower_bound(p + 1, p + 1 + qwq, b[i]) - p];
    for (int i = 1; i <= tot && prime[i] <= n; ++i)
    {
        maxx[prime[i]][0] = 1;
        maxx[prime[i]][1] = maxx[prime[i]][2] = 0;
    }
    for (int i = 1; i <= qwq; ++i)
        for (int j = 1; j <= 3 && j <= cnt[i]; ++j)
            insert(p[i]);
    all = 1;
    for (int i = 1; i <= tot && prime[i] <= n; ++i)
        (all *= maxx[prime[i]][0]) %= mod;
    ll answer = 0;
    for (int i = 1; i <= qwq; ++i)
    {
        if (cnt[i] > 1)
            (answer += calc(p[i] * 2) * p[i] % mod * p[i] % mod * cnt[i] % mod * (cnt[i] - 1)) %= mod;
        del(p[i]);
        for (int j = i + 1; j <= qwq; ++j)
        {
            del(p[j]);
            (answer += calc(p[i] + p[j]) * p[i] % mod * p[j] % mod * cnt[i] % mod * cnt[j] * 2) %= mod;
            add(p[j]);
        }
        add(p[i]);
    }
    printf("%lld\n", answer);
}
signed main()
{
    init(5e5);
    int T = 1;
    read(T);
    while (T--)
        work();
    return 0;
}