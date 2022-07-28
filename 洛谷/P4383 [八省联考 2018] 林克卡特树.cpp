/**
 *    unicode: UTF-8
 *    name:    P4383 [八省联考 2018] 林克卡特树
 *    author:  wangjunrui
 *    created: 2022.07.21 周四 15:48:44 (Asia/Shanghai)
 **/
#include <cstdio>
#include <vector>
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
typedef pair<ll, int> node;
constexpr int N = 3e5 + 5;
int n, m;
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
node dp[N][3];
inline node operator+(const node &lhs, const node &rhs)
{
    return node(lhs.first + rhs.first, lhs.second + rhs.second);
}
inline node operator+(const node &lhs, const int &rhs)
{
    return node(lhs.first + rhs, lhs.second);
}
int minus;
inline node calc(node rhs)
{
    return node(rhs.first - minus, rhs.second + 1);
}
inline void dfs(int u, int _fa)
{
    dp[u][0] = dp[u][1] = dp[u][2] = node();
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        node maxx = max(dp[v][0], calc(max(dp[v][1], dp[v][2])));
        dp[u][2] = max(dp[u][2] + maxx, dp[u][1] + dp[v][1] + edge[i].dis);
        dp[u][1] = max(dp[u][1] + maxx, dp[u][0] + dp[v][1] + edge[i].dis);
        dp[u][0] = dp[u][0] + maxx;
    }
}
signed main()
{
    read(n, m);
    ++m;
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    int l = -1e9, r = 1e9, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        minus = mid;
        dfs(1, 0);
        if (max(dp[1][0], calc(max(dp[1][1], dp[1][2]))).second >= m)
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    minus = ans;
    dfs(1, 0);
    printf("%lld\n", max(dp[1][0], calc(max(dp[1][1], dp[1][2]))).first + (ll)ans * m);
    return 0;
}