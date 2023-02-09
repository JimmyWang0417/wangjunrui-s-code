/**
 *    unicode: UTF-8
 *    name:    CF1254D Tree Queries
 *    author:  whitepaperdog
 *    created: 2022.07.02 周六 13:08:29 (Asia/Shanghai)
 **/
#include <cassert>
#include <cstdio>
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
constexpr int N = 1.5e5 + 5;
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
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, a[N];
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int fa[N], dep[N];
int son[N], size[N];
int dfn[N], dfstime;
int top[N];
inline void dfs1(int u, int _fa)
{
    dep[u] = dep[fa[u] = _fa] + 1;
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
inline void dfs2(int u, int topf)
{
    top[u] = topf;
    dfn[u] = ++dfstime;
    if (son[u])
        dfs2(son[u], topf);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (top[v])
            continue;
        dfs2(v, v);
    }
}
int c[N];
inline void update(int pos, int val)
{
    assert(pos);
    for (int i = pos; i <= dfstime; i += lowbit(i))
        add(c[i], val);
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        add(res, c[i]);
    return res;
}
inline int query(int l, int r)
{
    return (query(r) - query(l - 1) + mod) % mod;
}
signed main()
{
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    ll invn = quickpow(n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, v, d;
        read(opt, v);
        if (opt == 1)
        {
            read(d);
            update(1, (int)((ll)size[v] * d % mod));
            update(dfn[v], (int)((ll)(n - size[v]) * d % mod));
            if (son[v])
                update(dfn[son[v]], (int)((ll)(mod - size[son[v]]) * d % mod));
            add(a[v], d);
        }
        else
        {
            ll res = 0;
            while (top[v] != 1)
            {
                (res += query(dfn[top[v]], dfn[v]) - (ll)a[fa[top[v]]] * size[top[v]]) %= mod;
                v = fa[top[v]];
            }
            (res += query(dfn[v])) %= mod;
            printf("%lld\n", (res + mod) % mod * invn % mod);
        }
    }
    return 0;
}