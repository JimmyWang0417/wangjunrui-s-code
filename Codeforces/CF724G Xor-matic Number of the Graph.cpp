/**
 *    unicode: UTF-8
 *    name:    project
 *    author:  wangjunrui
 *    created: 2022.07.09 周六 10:12:36 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
int n, m;
struct Edge
{
    int next, to;
    ll dis;
} edge[N * 4];
int head[N], num_edge;
inline void add_edge(int from, int to, ll dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
ll d[65], cnt;
inline void insert(ll val)
{
    for (int i = 60; i >= 0; --i)
        if ((val >> i) & 1)
        {
            if (!d[i])
            {
                d[i] = val;
                ++cnt;
                break;
            }
            else
                val ^= d[i];
        }
}
#define size sze
bool vis[N];
ll p[N];
int tot;
ll dis[N];
int size;
inline void dfs(int u, int _fa)
{
    ++size;
    vis[u] = true;
    p[++tot] = dis[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        if (!vis[v])
        {
            dis[v] = dis[u] ^ edge[i].dis;
            dfs(v, u);
        }
        else
            insert(dis[u] ^ dis[v] ^ edge[i].dis);
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        ll w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    ll res = 0;
    for (int root = 1; root <= n; ++root)
        if (!vis[root])
        {
            dfs(root, 0);
            for (int i = 60; i >= 0; --i)
            {
                bool flag = false;
                for (int j = 60; j >= 0; --j)
                    if ((d[j] >> i) & 1)
                    {
                        flag = true;
                        break;
                    }
                if (flag)
                    (res += (ll)size * (size - 1) / 2 % mod * ((1ll << (cnt - 1)) % mod) % mod * ((1ll << i) % mod)) %= mod;
                else
                {
                    int x = 0;
                    for (int j = 1; j <= tot; ++j)
                        if ((p[j] >> i) & 1)
                            ++x;
                    (res += (ll)x * (size - x) % mod * ((1ll << cnt) % mod) % mod * ((1ll << i) % mod)) %= mod;
                }
            }
            cnt = tot = size = 0;
            memset(d, 0, sizeof(d));
        }
    printf("%lld\n", res);
    return 0;
}