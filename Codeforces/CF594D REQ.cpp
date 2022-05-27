#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 1e6 + 5;
constexpr int mod = 1e9 + 7;
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
int n, m;
int a[N];
int prime[N], tot;
int vis[N];
ll b[N], c[N];
int las[N];
inline void getprimes(int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            vis[i] = i;
            b[i] = (i - 1) * quickpow(i, mod - 2) % mod;
            c[i] = quickpow(b[i], mod - 2);
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = prime[j];
            if (i % prime[j] == 0)
                break;
        }
    }
}
ll sum[N];
inline void update(int pos, ll val)
{
    for (int i = pos; i <= n; i += lowbit(i))
        (sum[i] *= val) %= mod;
}
inline ll query(int pos)
{
    ll res = 1;
    for (int i = pos; i; i -= lowbit(i))
        (res *= sum[i]) %= mod;
    return res;
}
inline ll query(int l, int r)
{
    return query(r) * quickpow(query(l - 1), mod - 2) % mod;
}
inline void insert(int pos, int val)
{
    update(pos, val);
    while (val > 1)
    {
        const int &res = vis[val];
        update(pos, b[res]);
        if (las[res])
            update(las[res], c[res]);
        las[res] = pos;
        val /= res;
    }
}
list<pair<int, int>> g[N];
ll answer[N];
signed main()
{
    getprimes(1e6);
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        read(l, r);
        g[r].push_back(make_pair(l, i));
    }
    for (int i = 1; i <= n; ++i)
        sum[i] = 1;
    for (int r = 1; r <= n; ++r)
    {
        insert(r, a[r]);
        for (auto v : g[r])
            answer[v.second] = query(v.first, r);
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}