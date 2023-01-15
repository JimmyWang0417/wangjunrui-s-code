/**
 *    unicode: UTF-8
 *    name:    P5284 [十二省联考 2019] 字符串问题
 *    author:  whitepaperdog
 *    created: 2022.08.05 周五 19:53:45 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
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
constexpr int N = 4e5 + 5, M = 1e6 + 5;
char str[N];
vector<int> graph[N];
struct Point
{
    int ch[26], len;
    int fa;
} point[N];
int las = 1, tot = 1;
int where[N];
inline void insert(int c)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
}
int fa[N][25];
inline void dfs(int u)
{
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    for (auto v : graph[u])
    {
        fa[v][0] = u;
        dfs(v);
    }
}
inline int calc(int u, int len)
{
    for (int i = 20; i >= 0; --i)
        if (point[fa[u][i]].len >= len)
            u = fa[u][i];
    return u;
}
vector<pair<int, int>> g[N];
struct Edge
{
    int next, to, dis;
} edge[M];
int head[M], num_edge;
int deg[M];
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
    ++deg[to];
}
ll dp[M];
inline void clear(int limit)
{
    fill(head + 1, head + 1 + limit, 0);
    fill(dp + 1, dp + 1 + limit, 0);
    fill(deg + 1, deg + 1 + limit, 0);
    for (int i = 1; i <= tot; ++i)
    {
        memset(point[i].ch, 0, sizeof(point[i].ch));
        memset(fa[i], 0, sizeof(fa[i]));
        g[i].clear();
        graph[i].clear();
    }
    las = tot = 1;
    num_edge = 0;
}
inline void work()
{
    int n, m, q;
    scanf("%s", str + 1);
    int len = (int)strlen(str + 1);
    reverse(str + 1, str + 1 + len);
    for (int i = 1; str[i]; ++i)
    {
        insert(str[i] - 'a');
        where[i] = las;
    }
    for (int i = 2; i <= tot; ++i)
        graph[point[i].fa].push_back(i);
    dfs(1);
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int l, r;
        read(l, r);
        l = len - l + 1;
        r = len - r + 1;
        swap(l, r);
        g[calc(where[r], r - l + 1)].emplace_back(r - l + 1, i);
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        read(l, r);
        l = len - l + 1;
        r = len - r + 1;
        swap(l, r);
        g[calc(where[r], r - l + 1)].emplace_back(r - l + 1, i + n);
    }
    for (int i = 2; i <= tot; ++i)
    {
    int qwq = point[i].fa + n + m;
    sort(g[i].begin(), g[i].end(),
    [](const pair<int, int> x, const pair<int, int> y)
    { return x.first == y.first ? x.second > y.second : x.first < y.first; });
    for (auto u : g[i])
    if (u.second <= n)
    add_edge(qwq, u.second, u.first);
    else
    {
    add_edge(qwq, u.second, 0);
    qwq = u.second;
    }
    add_edge(qwq, i + n + m, 0);
    }
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v + n, 0);
    }
    int limit = n + m + tot;
    queue<int> que;
    for (int i = 1; i <= limit; ++i)
        if (!deg[i])
            que.push(i);
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            ckmax(dp[v], dp[u] + edge[i].dis);
            if (!--deg[v])
                que.push(v);
        }
    }
    ll res = 0;
    for (int i = 1; i <= limit; ++i)
        if (deg[i])
        {
            clear(limit);
            printf("-1\n");
            return;
        }
        else
            ckmax(res, dp[i]);
    printf("%lld\n", res);
    clear(limit);
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}