#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
using namespace std;
const int N = 1e5 + 5;
int n, m;
struct Edge
{
    int next, to, dis;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
vector<int> g[N], revg[N];
ll dis[N], dp[N];
inline bool check(int u)
{
    int las = dp[u];
    dp[u] = dis[u];
    for (auto v : g[u])
        dp[u] = max(dp[u], dp[v]);
    return las > dp[u];
}
bool exist[N];
inline void spfa()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(dp, 0x3f, sizeof(dp));
    queue<int> q;
    dp[1] = dis[1] = 0;
    q.push(1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (auto v : revg[u])
            if (check(v))
            {
                if (!exist[v])
                {
                    q.push(v);
                    exist[v] = true;
                }
            }
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dp[u] + edge[i].dis)
            {
                dis[v] = dp[u] + edge[i].dis;
                if (check(v))
                {
                    if (!exist[v])
                    {
                        q.push(v);
                        exist[v] = true;
                    }
                }
            }
        }
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
    }
    for (int i = 1; i <= n; ++i)
    {
        int c;
        read(c);
        for (int j = 1, x; j <= c; ++j)
        {
            read(x);
            g[i].push_back(x);
            revg[x].push_back(i);
        }
    }
    spfa();
    printf("%lld\n", dp[n]);
    return 0;
}