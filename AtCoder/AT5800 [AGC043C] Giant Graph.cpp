#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e5 + 5;
const int mod = 998244353;
int n;
ll power[N];
class Graph
{
public:
    int m;
    int maxsg;
    int sg[N];
    ll dp[N];
    struct Edge
    {
        int next, to;
    } edge[N];
    int head[N], num_edge;
    inline void add_edge(int from, int to)
    {
        edge[++num_edge].next = head[from];
        edge[num_edge].to = to;
        head[from] = num_edge;
    }
    inline void work()
    {
        read(m);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            read(u, v);
            if (u > v)
                swap(u, v);
            add_edge(u, v);
        }
        for (int u = n; u >= 1; --u)
        {
            set<int> mex;
            for (int e = head[u]; e; e = edge[e].next)
            {
                int &v = edge[e].to;
                mex.insert(sg[v]);
            }
            while (mex.count(sg[u]))
                ++sg[u];
            (dp[sg[u]] += power[u]) %= mod;
            maxsg = max(maxsg, sg[u]);
        }
    }
} g[3];
signed main()
{
    read(n);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
        power[i] = (power[i - 1] * 716070898ll % mod);
    g[0].work(), g[1].work(), g[2].work();
    ll ans = 0;
    for (int i = 0; i <= g[0].maxsg; ++i)
        for (int j = 0; j <= g[1].maxsg; ++j)
            (ans += g[0].dp[i] * g[1].dp[j] % mod * g[2].dp[i ^ j] % mod) %= mod;
    printf("%lld\n", ans);
    return 0;
}
