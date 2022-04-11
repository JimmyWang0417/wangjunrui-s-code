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
constexpr int N = 2e6 + 5;
int n, a[N];
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
ll sum;
bool dis[25][N];
inline int dfs(int u, int dep)
{
    int res = a[u];
    for (int i = 0; i <= 20; ++i)
        dis[i][(dep + a[u]) & ((1 << i) - 1)] ^= 1;
    for (int i = 0; i <= 20; ++i)
        res ^= dis[i][dep & ((1 << i) - 1)] << i;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        res ^= dfs(v, dep + 1);
    }
    for (int i = 0; i <= 20; ++i)
        res ^= dis[i][dep & ((1 << i) - 1)] << i;
    sum += res;
    return res;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa);
        add_edge(_fa, i);
    }
    dfs(1, 0);
    printf("%lld\n", sum);
    return 0;
}