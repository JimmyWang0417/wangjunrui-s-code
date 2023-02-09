#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
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
constexpr int N = 1e5 + 5;
int n, m;
int inv;
inline void exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}
int power[N], invpower[N];
struct Edge
{
    int next, to, dis;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
bool vis[N];
int size[N], maxsize[N], root, sum;
inline void getroot(int u, int _fa)
{
    maxsize[u] = 0;
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        getroot(v, u);
        size[u] += size[v];
        ckmax(maxsize[u], size[v]);
    }
    ckmax(maxsize[u], sum - size[u]);
    if (maxsize[u] < maxsize[root])
        root = u;
}
inline void dfs(int u, int _fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        dfs(v, u);
        size[u] += size[v];
    }
}
int f[N], g[N], dep[N];
__gnu_pbds::gp_hash_table<int, int> mp1, mp2;
ll answer;
inline void calc(int u, int _fa)
{
    answer += mp1[f[u]] + mp2[(int)((m - (ll)g[u] * invpower[dep[u] + 1] % m) % m)];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        dep[v] = dep[u] + 1;
        f[v] = (int)((f[u] + (ll)edge[i].dis * power[dep[v]]) % m);
        g[v] = (int)((g[u] * 10ll + edge[i].dis) % m);
        calc(v, u);
    }
}
inline void add(int u, int _fa)
{
    ++mp1[(int)((m - (ll)g[u] * invpower[dep[u] + 1] % m) % m)];
    ++mp2[f[u]];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        add(v, u);
    }
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    dfs(u, 0);
    vis[u] = true;
    mp1[0] = mp2[0] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        f[v] = g[v] = edge[i].dis % m;
        dep[v] = 0;
        calc(v, u);
        add(v, u);
    }
    mp1.clear(), mp2.clear();
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = size[v];
        solve(v);
    }
}
signed main()
{
    read(n, m);
    int abab;
    exgcd(10, m, inv, abab);
    ((inv %= m) += m) %= m;
    power[0] = invpower[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power[i] = (int)(power[i - 1] * 10ll % m);
        invpower[i] = (int)((ll)invpower[i - 1] * inv % m);
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        ++u, ++v;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    maxsize[0] = sum = n;
    solve(1);
    printf("%lld\n", answer);
    return 0;
}