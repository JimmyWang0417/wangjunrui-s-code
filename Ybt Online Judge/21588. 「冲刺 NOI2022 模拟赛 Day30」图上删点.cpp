#include <cstdio>
#include <cstring>
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
constexpr int N = 1e5 + 5, M = 1e7 + 5;
int prime[N], tot;
bool vis[N];
inline void getprimes(int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int n;
struct Edge
{
    int next, to;
} edge[M * 4];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int dfn[N], low[N], dfstime;
int size[N], all;
inline void dfs(int u)
{
    size[u] = 1;
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        dfs(v);
        size[u] += size[v];
    }
}
int answer;
inline void tarjan(int u, int _fa)
{
    dfn[u] = low[u] = ++dfstime;
    int maxx = 0, left = all - 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        if (!dfn[v])
        {
            tarjan(v, u);
            ckmin(low[u], low[v]);
            if (dfn[u] <= low[v])
            {
                ckmax(maxx, size[v]);
                left -= size[v];
            }
        }
        else
            ckmin(low[u], dfn[v]);
    }
    ckmax(maxx, left);
    ckmin(answer, maxx);
}
int where[M], cnt;
vector<int> g[M];
int st[N], top;
inline void solve(int x, int id)
{
    for (int i = 1; i <= tot && prime[i] * prime[i] <= x; ++i)
        if (x % prime[i] == 0)
        {
            st[++top] = prime[i];
            int nmsl = 0;
            while (x % prime[i] == 0)
            {
                x /= prime[i];
                ++nmsl;
            }
            if (nmsl >= 2)
            {
                if (!where[prime[i] * prime[i]])
                    where[prime[i] * prime[i]] = ++cnt;
                g[where[prime[i] * prime[i]]].push_back(id);
            }
        }
    if (x > 1)
        st[++top] = x;
    for (int i = 1; i < top; ++i)
        for (int j = i + 1; j <= top; ++j)
        {
            if (!where[st[i] * st[j]])
                where[st[i] * st[j]] = ++cnt;
            g[where[st[i] * st[j]]].push_back(id);
        }
    top = 0;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("appoint.in", "r", stdin);
    freopen("appoint.out", "w", stdout);
#endif
    getprimes(3200);
    int T;
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)
        {
            int x;
            read(x);
            solve(x, i);
        }
        for (int i = 1; i <= cnt; ++i)
        {
            if (g[i].empty())
                continue;
            for (int j = 1; j < (int)g[i].size(); ++j)
            {
                add_edge(g[i][j - 1], g[i][j]);
                add_edge(g[i][j], g[i][j - 1]);
            }
            add_edge(g[i].front(), g[i].back());
            add_edge(g[i].back(), g[i].front());
            g[i].clear();
        }
        memset(vis, 0, sizeof(vis));
        int res0 = 0, res1 = 0;
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
            {
                dfs(i);
                answer = 0x7ffffff;
                all = size[i];
                tarjan(i, 0);
                res1 = min(max(res0, answer), max(res1, all));
                res0 = max(res0, all);
            }
        printf("%d\n", res1);
        memset(head, num_edge = 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(where, 0, sizeof(where));
        dfstime = cnt = 0;
    }
    return 0;
}
