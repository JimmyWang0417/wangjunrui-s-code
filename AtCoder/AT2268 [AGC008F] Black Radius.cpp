#include <algorithm>
#include <cstdio>
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
constexpr int N = 2e6 + 5;
int n;
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
#define size qwq
char str[N];
int fi[N], se[N];
int dp[N];
int size[N];
inline void dfs1(int u, int _fa)
{
    if (str[u] == '1')
        size[u] = 1;
    else
        dp[u] = 0x3f3f3f3f;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        size[u] += size[v];
        if (fi[u] <= fi[v])
        {
            se[u] = fi[u];
            fi[u] = fi[v] + 1;
        }
        else if (se[u] <= fi[v])
            se[u] = fi[v] + 1;
        if (size[v])
            ckmin(dp[u], fi[v] + 1);
    }
}
ll answer;
inline void dfs2(int u, int _fa)
{
    if (_fa)
    {
        int len = (fi[_fa] == fi[u] + 1 ? se[_fa] : fi[_fa]) + 1;
        if (fi[u] < len)
        {
            se[u] = fi[u];
            fi[u] = len;
        }
        else if (se[u] < len)
            se[u] = len;
        if (size[1] - size[u])
            ckmin(dp[u], len);
    }
    int limit = min(fi[u] - 1, se[u] + 1);
    if (dp[u] <= limit)
        answer += limit - dp[u] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs2(v, u);
    }
}
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    scanf("%s", str + 1);
    dfs1(1, 0);
    dfs2(1, 0);
    printf("%lld\n", answer + 1);
    return 0;
}