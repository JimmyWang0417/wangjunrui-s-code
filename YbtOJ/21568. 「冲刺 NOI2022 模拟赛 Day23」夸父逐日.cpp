#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
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
constexpr int N = 1e5 + 5, M = 55, K = 5e6 + 5;
int n, m, d;
struct Edge
{
    int next, to;
} edge[K];
int head[K], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
inline int calc(int where, int day)
{
    return day * n + where;
}
int dfn[K], low[K], dfstime;
int st[K], top;
int belong[K], color;
inline void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (!dfn[v])
        {
            tarjan(v);
            ckmin(low[u], low[v]);
        }
        else if (!belong[v])
            ckmin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        belong[u] = ++color;
        while (st[top] != u)
            belong[st[top--]] = color;
        --top;
    }
}
char str[M];
int cnt[K];
list<int> g[K];
int in[K];
int dis[K];
bool mp[M];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("chase.in", "r", stdin);
    freopen("chase.out", "w", stdout);
#endif
    read(n, m, d);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        for (int j = 0; j < d; ++j)
            add_edge(calc(u, j), calc(v, (j + 1) % d));
    }
    for (int i = 1; i <= n * d; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str);
        for (int j = 0; j < d; ++j)
        {
            if (str[j] == '0' || mp[j])
                continue;
            ++cnt[belong[calc(i, j)]];
            for (int k = j + 1; k < d; ++k)
                if (str[k] == '1')
                    mp[k] |= (belong[calc(i, j)] == belong[calc(i, k)]);
        }
        memset(mp, 0, sizeof(mp));
    }
    for (int u = 1; u <= n * d; ++u)
    {
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (belong[u] == belong[v])
                continue;
            g[belong[u]].push_back(belong[v]);
            ++in[belong[v]];
        }
    }
    queue<int> q;
    memset(dis, ~0x3f, sizeof(dis));
    dis[belong[calc(1, 0)]] = 0;
    for (int u = 1; u <= n * d; ++u)
        if (!in[u])
            q.push(u);
    int answer = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ckmax(answer, dis[u] += cnt[u]);
        for (auto v : g[u])
        {
            ckmax(dis[v], dis[u]);
            if (!--in[v])
                q.push(v);
        }
    }
    printf("%d\n", answer);
    return 0;
}
