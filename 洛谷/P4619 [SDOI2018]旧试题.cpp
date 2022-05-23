#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
int prime[N], tot;
int mul[N];
bool vis[N];
int f[N], g[N], h[N];
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
            if (i % prime[j] == 0)
                break;
            mul[i * prime[j]] = -mul[i];
        }
    }
}
int deg[N];
struct node
{
    int u, v, w;
} e[N * 20];
int ybt;
struct Edge
{
    int next, to, dis;
} edge[N * 20];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int id[N], cnt;
int where[N];
int lasedge[N];
inline void work()
{
    int n, X, Y, Z;
    read(X, Y, Z);
    n = max(X, max(Y, Z));
    for (int i = 1; i <= X; ++i)
    {
        for (int j = i; j <= X; j += i)
            (f[i] += X / j) %= mod;
    }
    for (int i = 1; i <= Y; ++i)
    {
        for (int j = i; j <= Y; j += i)
            (g[i] += Y / j) %= mod;
    }
    for (int i = 1; i <= Z; ++i)
    {
        for (int j = i; j <= Z; j += i)
            (h[i] += Z / j) %= mod;
    }
    for (int d = 1; d <= n; ++d)
        for (int i = 1; i * i * d <= n; ++i)
            if (mul[i * d])
                for (int j = i + 1; i * j * d <= n; ++j)
                    if (mul[j * d] && __gcd(i, j) == 1)
                    {
                        ++ybt;
                        e[ybt].u = i * d, e[ybt].v = j * d, e[ybt].w = i * j * d;
                        ++deg[i * d], ++deg[j * d];
                    }
    for (int i = 1; i <= n; ++i)
        if (mul[i])
            id[++cnt] = i;
    sort(id + 1, id + 1 + cnt, [](int x, int y) { return deg[x] > deg[y]; });
    for (int i = 1; i <= cnt; ++i)
        where[id[i]] = i;
    for (int i = 1; i <= ybt; ++i)
    {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (deg[u] < deg[v])
            swap(u, v);
        add_edge(u, v, w);
    }
    ll answer = 0;
    for (int i = 1; i <= cnt; ++i)
    {
        int x, y, z;
        int u = id[i];
        // case 1
        (answer += mul[u] * (ll)f[u] * g[u] % mod * h[u]) %= mod;
        for (int e = head[u]; e; e = edge[e].next)
        {
            int &v = edge[e].to;
            lasedge[v] = e;
        }
        for (int e1 = head[u]; e1; e1 = edge[e1].next)
        {
            int &v = edge[e1].to;
            // case2
            x = u, y = edge[e1].dis;
            (answer += mul[v] * (ll)f[x] * g[y] % mod * h[y]) %= mod;
            (answer += mul[v] * (ll)f[y] * g[x] % mod * h[y]) %= mod;
            (answer += mul[v] * (ll)f[y] * g[y] % mod * h[x]) %= mod;

            x = v, y = edge[e1].dis;
            (answer += mul[u] * (ll)f[x] * g[y] % mod * h[y]) %= mod;
            (answer += mul[u] * (ll)f[y] * g[x] % mod * h[y]) %= mod;
            (answer += mul[u] * (ll)f[y] * g[y] % mod * h[x]) %= mod;

            for (int e2 = head[v]; e2; e2 = edge[e2].next)
            {
                int &w = edge[e2].to;
                if (lasedge[w])
                {
                    x = edge[e1].dis, y = edge[e2].dis, z = edge[lasedge[w]].dis;
                    ll cur = 0;
                    //case 3
                    (cur += (ll)f[x] * g[y] % mod * h[z]) %= mod;
                    (cur += (ll)f[x] * g[z] % mod * h[y]) %= mod;
                    (cur += (ll)f[y] * g[x] % mod * h[z]) %= mod;
                    (cur += (ll)f[y] * g[z] % mod * h[x]) %= mod;
                    (cur += (ll)f[z] * g[x] % mod * h[y]) %= mod;
                    (cur += (ll)f[z] * g[y] % mod * h[x]) %= mod;
                    (answer += mul[u] * mul[v] * mul[w] * cur) %= mod;
                }
            }
        }

        for (int e = head[u]; e; e = edge[e].next)
        {
            int &v = edge[e].to;
            lasedge[v] = 0;
        }
    }
    printf("%lld\n", (answer + mod) % mod);
    memset(head, num_edge = 0, sizeof(head));
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(h, 0, sizeof(h));
    memset(deg, 0, sizeof(deg));
    ybt = cnt = 0;
}
signed main()
{
    getprime(1e5);
    int T = 1;
    read(T);
    while (T--)
        work();
    return 0;
}
