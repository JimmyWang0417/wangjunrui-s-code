#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <algorithm>
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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
struct tree_array
{
    int c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= 1e5; i += lowbit(i))
            (c[i] += val) %= mod;
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            (res += c[i]) %= mod;
        return res;
    }
    inline int query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
} tree;
int prime[N], tot, mul[N];
bool vis[N];
inline void getprime(int n)
{
    mul[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            mul[i] = -1;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j])
                mul[i * prime[j]] = -mul[i];
            else
                break;
        }
    }
}
inline ll calc(int x)
{
    return (ll)x * (x + 1) / 2 % mod;
}
struct node
{
    int n, m, a, id;
    inline bool operator<(const node &rhs) const
    {
        return a < rhs.a;
    }
} a[N];
int T = 1;
int f[N];
inline void update(int i)
{
    for (int j = 1; i * j <= 1e5; ++j)
    {
        tree.update(i * j, (int)((ll)mul[j] * (i * j) * j % mod));
        (f[i * j] += (int)((ll)mul[j] * (i * j) * j % mod)) %= mod;
    }
}
ll answer[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
#endif
    getprime(1e5);
    read(T);
    for (int i = 1; i <= T; ++i)
    {
        read(a[i].n, a[i].m, a[i].a);
        a[i].id = i;
    }
    sort(a + 1, a + 1 + T);
    for (int kase = 1, nowa = 0; kase <= T; ++kase)
    {
        while (nowa < a[kase].a)
            update(++nowa);
        int n = a[kase].n, m = a[kase].m;
        ll res = 0;
        for (int l = 1, r = 0; l <= n && l <= m; l = r + 1)
        {
            r = min(n / (n / l), m / (m / l));
            (res += (tree.query(r) - tree.query(l - 1)) * calc(n / l) % mod * calc(m / l)) %= mod;
        }
        answer[a[kase].id] = (res + mod) % mod;
    }
    for (int i = 1; i <= T; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}
