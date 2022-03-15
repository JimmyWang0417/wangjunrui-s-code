#include <cstdio>
#include <vector>
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
constexpr int N = 35, M = 1005, K = N * N * N;
int n, m;
struct Edge
{
    int next, to;
} edge[K * M];
int head[K], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
struct node
{
    int l[4], r[4];
} a[M];
char str[N];
bool exist[K];
int dfn[K], low[K], dfstime;
int belong[K], color;
int st[K], top;
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
    if (low[u] == dfn[u])
    {
        belong[u] = ++color;
        while (st[top] != u)
            belong[st[top--]] = color;
        --top;
    }
}
int in[K];
vector<int> g[K];
ll C[N][N];
ll val[K], dis[K];
signed main()
{
    freopen("character.in", "r", stdin);
    freopen("character.out", "w", stdout);
    read(n, m);
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%s", str + 1);
        for (int j = 1; str[j]; ++j)
        {
            ++a[i].l[str[j] - 'A'];
            --a[i].r[str[j] - 'A'];
        }
        scanf("%s", str + 1);
        for (int j = 1; str[j]; ++j)
            ++a[i].r[str[j] - 'A'];
    }
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; i + j <= n; ++j)
            for (int k = 0; i + j + k <= n; ++k)
            {
                int u = i * (n + 1) * (n + 1) + j * (n + 1) + k;
                exist[u] = true;
                for (int e = 1; e <= m; ++e)
                    if (i >= a[e].l[0] && j >= a[e].l[1] && k >= a[e].l[2] && n - i - j - k >= a[e].l[3])
                    {
                        int v = (i + a[e].r[0]) * (n + 1) * (n + 1) + (j + a[e].r[1]) * (n + 1) + (k + a[e].r[2]);
                        add_edge(u, v);
                    }
            }
    }
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; i + j <= n; ++j)
            for (int k = 0; i + j + k <= n; ++k)
            {
                int u = i * (n + 1) * (n + 1) + j * (n + 1) + k;
                if (exist[u] && !dfn[u])
                    tarjan(u);
            }
    }
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; i + j <= n; ++j)
            for (int k = 0; i + j + k <= n; ++k)
            {
                int u = i * (n + 1) * (n + 1) + j * (n + 1) + k;
                val[belong[u]] += C[n][i] * C[n - i][j] * C[n - i - j][k];
                for (int e = head[u]; e; e = edge[e].next)
                {
                    int &v = edge[e].to;
                    if (belong[u] == belong[v])
                        continue;
                    ++in[belong[v]];
                    g[belong[u]].push_back(belong[v]);
                }
            }
    }
    queue<int> q;
    for (int i = 1; i <= color; ++i)
        if (!in[i])
            q.push(i);
    ll res = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        dis[u] += val[u];
        ckmax(res, dis[u]);
        for (auto v : g[u])
        {
            ckmax(dis[v], dis[u]);
            if (!--in[v])
                q.push(v);
        }
    }
    printf("%lld\n", res);
    return 0;
}