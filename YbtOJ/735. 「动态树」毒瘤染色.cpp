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
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
ll fac[N], inv[N];
inline ll C(int n, int m)
{
    if (m < 0 || n < m)
        return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
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
int n, m, q, ww;
struct Tree
{
    int ch[2], fa;
    int size;
    bool ans;
    bool rev;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
inline bool check(int x)
{
    return rc(fa(x)) == x;
}
inline bool nroot(int x)
{
    return lc(fa(x)) == x || rc(fa(x)) == x;
}
inline void pushup(int x)
{
    tree[x].ans = ((x > n) || tree[lc(x)].ans || tree[rc(x)].ans);
}
inline void pushdown(int x)
{
    if (tree[x].rev)
    {
        swap(lc(x), rc(x));
        if (lc(x))
            tree[lc(x)].rev ^= 1;
        if (rc(x))
            tree[rc(x)].rev ^= 1;
        tree[x].rev = false;
    }
}
inline void rotate(int x)
{
    int y = fa(x), z = fa(y), k = check(x), w = tree[x].ch[k ^ 1];

    if (nroot(y))
        tree[z].ch[check(y)] = x;
    fa(x) = z;

    tree[x].ch[k ^ 1] = y;
    fa(y) = x;

    tree[y].ch[k] = w;
    if (w)
        fa(w) = y;

    pushup(y), pushup(x), pushup(z);
}
int st[N], top;
inline void splay(int x)
{
    st[top = 1] = x;
    for (int y = x; nroot(y); y = fa(y))
        st[++top] = fa(y);
    while (top)
        pushdown(st[top--]);
    while (nroot(x))
    {
        if (nroot(fa(x)))
            rotate(check(x) == check(fa(x)) ? fa(x) : x);
        rotate(x);
    }
}
inline void access(int x)
{
    for (int y = 0; x; x = fa(y = x))
    {
        splay(x);
        rc(x) = y;
        pushup(x);
    }
}
inline int findroot(int x)
{
    access(x);
    splay(x);
    while (pushdown(x), lc(x))
        x = lc(x);
    splay(x);
    return x;
}
inline void makeroot(int x)
{
    access(x);
    splay(x);
    tree[x].rev ^= 1;
}
inline void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
inline void link(int x, int y)
{
    makeroot(x);
    fa(x) = y;
}
int need;
inline void dfs(int u, int goal)
{
    if (!u)
        return;
    ++need;
    dfs(lc(u), goal), dfs(rc(u), goal);
    lc(u) = rc(u) = 0;
    fa(u) = goal;
}
ll f[N];
inline ll calc(int u)
{
    if (!ww)
        return f[u];
    ll res = f[u];
    for (int i = 0; i <= u; ++i)
        (res += ((i & 1) ? mod - 1 : 1) * f[i] % mod * C(u, i)) %= mod;
    return res;
}
signed main()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    read(n, m, q, ww);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    inv[n] = quickpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    for (int i = 0; i <= n; ++i)
        f[i] = quickpow((n - i) * quickpow(n, mod - 2) % mod, q) % mod;
    int cnt = n;
    ll g1 = calc(1), g2 = calc(2), answer = n * g1 % mod;
    int lastans = 0;
    while (m--)
    {
        int u, v;
        read(u, v);
        u ^= lastans, v ^= lastans;
        if (u == v)
        {
            printf("%d\n", lastans = (int)answer);
            continue;
        }
        if (findroot(u) == findroot(v))
        {
            if (split(u, v), tree[v].ans)
            {
                printf("%d\n", lastans = (int)answer);
                continue;
            }
            need = 0;
            dfs(v, ++cnt);
            pushup(cnt);
            (answer += calc(need) - g2 + mod) %= mod;
        }
        else
        {
            link(u, v);
            (answer += mod - g2) %= mod;
        }
        printf("%d\n", lastans = (int)answer);
    }
    return 0;
}