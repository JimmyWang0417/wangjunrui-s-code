#include <bitset>
#include <cstdio>
#include <vector>
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
constexpr int N = 47, M = (1 << 25) + 5;
int n, m;
struct Edge
{
    int next, to, dis;
} edge[N * N];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
bitset<N> visA, visB, where;
vector<int> A, B;
int id[N];
int times;
namespace subtask1
{
    int dp[M];
    ll f[N], g[N];
    inline void main()
    {
        for (int i = 0; i < (int)A.size(); ++i)
        {
            int u = A[i];
            for (int e = head[u]; e; e = edge[e].next)
            {
                int &v = edge[e].to;
                if (visB[v])
                {
                    f[i] |= 1ll << id[v];
                    if (!(where[u] ^ edge[e].dis))
                        g[i] |= 1ll << id[v];
                }
            }
        }
        dp[0] = times;
        for (int S = 0; S < (1 << A.size()); ++S)
        {
            ll G = 0;
            for (int i = 0; i < (int)A.size(); ++i)
                if ((S >> i) & 1)
                    G |= f[i];
            for (int i = 0; i < (int)A.size(); ++i)
            {
                if ((S >> i) & 1)
                    continue;
                ckmax(dp[S | (1 << i)], dp[S] + __builtin_popcountll((~G) & g[i]));
            }
        }
        printf("%d\n", dp[(1 << A.size()) - 1]);
    }
}
namespace subtask2
{
    int dp[M];
    int f[N], g[N];
    inline void main()
    {
        for (int i = 0; i < (int)A.size(); ++i)
        {
            int u = A[i];
            for (int e = head[u]; e; e = edge[e].next)
            {
                int &v = edge[e].to;
                if (visB[v])
                {
                    f[i] |= 1 << id[v];
                    if (!(where[u] ^ edge[e].dis))
                        g[i] |= 1 << id[v];
                }
            }
        }
        dp[0] = times;
        int res = 0;
        for (int S = 0; S < (1 << B.size()); ++S)
        {
            for (int i = 0; i < (int)A.size(); ++i)
                ckmax(dp[S | f[i]], dp[S] + __builtin_popcountll((~S) & g[i]));
            ckmax(res, dp[S]);
        }
        printf("%d\n", res);
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("brothers.in", "r", stdin);
    freopen("brothers.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int e = head[1]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        visA.set(v);
        if (edge[e].dis)
            where.set(v);
        else
            ++times;
    }
    for (int u = 1; u <= n; ++u)
    {
        for (int e = head[u]; e; e = edge[e].next)
        {
            int &v = edge[e].to;
            if (v == 1 || visA[v])
                continue;
            visB.set(v);
        }
    }
    for (int u = 1; u <= n; ++u)
    {
        if (visA[u])
            A.push_back(u);
        if (visB[u])
        {
            id[u] = (int)B.size();
            B.push_back(u);
        }
    }
    if (A.size() < B.size())
        subtask1::main();
    else
        subtask2::main();
    return 0;
}