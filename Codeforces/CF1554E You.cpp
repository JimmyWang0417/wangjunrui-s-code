#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
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
constexpr int mod = 998244353;
int n;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
int deg[N], qwq[N];
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
    ++qwq[from];
}
int dp[N];
bool vis[N];
int a[N], b[N];
inline void calc(int x)
{
    memcpy(deg, qwq, sizeof(qwq));
    memset(vis, 0, sizeof(vis));
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (vis[v])
                continue;
            if (!a[u])
            {
                (a[v] += 1) %= x;
                ++b[v];
            }
            else
            {
                (a[u] += 1) %= x;
                ++b[u];
            }
            if (--deg[v] == 1)
                q.push(v);
        }
    }
    int ans = b[1];
    for (int i = 2; i <= n; ++i)
        ans = __gcd(ans, b[i]);
    if (ans % x == 0)
        dp[ans] = 1;
}
inline void solve(int x)
{
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
        {
            calc(i);
            do
                x /= i;
            while (x % i == 0);
        }
    if (x > 1)
        calc(x);
}
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            read(u, v);
            add_edge(u, v);
            add_edge(v, u);
        }
        solve(n - 1);
        dp[1] = 1;
        for (int i = 1; i < n; ++i)
            (dp[1] *= 2) %= mod;
        for (int i = 2; i <= n; ++i)
            (dp[1] -= dp[i]) %= mod;
        for (int i = 1; i <= n; ++i)
            printf("%d ", (dp[i] + mod) % mod);
        putchar('\n');
        memset(head, num_edge = 0, sizeof(head));
        memset(qwq, 0, sizeof(qwq));
        memset(dp, 0, sizeof(dp));
    }
    return 0;
}