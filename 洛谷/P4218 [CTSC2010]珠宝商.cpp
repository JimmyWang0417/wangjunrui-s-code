#include <cmath>
#include <cstdio>
#include <cstring>
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
constexpr int N = 5e4 + 5;
int n, m;
int block;
struct SAM
{
    char str[N];
    int where[N];
    struct Point
    {
        int ch[26];
        int fa, len;
        int id;
    } point[N * 2];
    int link[N * 2][26];
    int las = 1, tot = 1;
    int dp[N * 2];
    int cnt[N * 2];
    inline void insert(int c, int id)
    {
        int p = las, np = las = where[id] = ++tot;
        point[np].len = point[p].len + 1;
        cnt[np] = 1;
        for (; p && !point[p].ch[c]; p = point[p].fa)
            point[p].ch[c] = np;
        if (!p)
            point[np].fa = 1;
        else
        {
            int q = point[p].ch[c];
            if (point[p].len + 1 == point[q].len)
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
        for (p = np; p && !point[p].id; p = point[p].fa)
            point[p].id = id;
    }
    struct Edge
    {
        int next, to;
    } edge[N * 2];
    int head[N * 2], num_edge;
    inline void add_edge(int from, int to)
    {
        edge[++num_edge].next = head[from];
        edge[num_edge].to = to;
        head[from] = num_edge;
    }
    inline void init(int u)
    {
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            init(v);
            cnt[u] += cnt[v];
            if (!link[u][str[point[v].id - point[u].len] - 'a'])
                link[u][str[point[v].id - point[u].len] - 'a'] = v;
        }
    }
    inline int calc(int u, int len, int c)
    {
        if (!u)
            return 0;
        if (point[u].len > len)
        {
            if (str[point[u].id - len] - 'a' == c)
                return u;
            else
                return 0;
        }
        else
            return link[u][c];
    }
    inline void init()
    {
        for (int i = 1; i <= m; ++i)
            insert(str[i] - 'a', i);
        for (int i = 2; i <= tot; ++i)
            add_edge(point[i].fa, i);
        init(1);
    }
    inline void dfs(int u)
    {
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            dp[v] += dp[u];
            dfs(v);
        }
    }
    inline void clear() { memset(dp, 0, sizeof(dp)); }
} A, B;
char str[N];
int a[N];
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
bool vis[N];
int size[N], maxsize[N], sum, root;
inline void getroot(int u, int _fa)
{
    size[u] = 1;
    maxsize[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        getroot(v, u);
        size[u] += size[v];
        ckmax(maxsize[u], size[v]);
    }
    ckmax(maxsize[u], sum - size[u]);
    if (maxsize[u] < maxsize[root])
        root = u;
}
int dep[N];
int f[N], g[N];
inline void dfs(int u, int _fa)
{
    size[u] = 1;
    dep[u] = dep[_fa] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        f[v] = A.calc(f[u], dep[u], a[v]);
        g[v] = B.calc(g[u], dep[u], a[v]);
        dfs(v, u);
        size[u] += size[v];
    }
}
ll answer;
inline void addblock(int u, int _fa, int res = 1)
{
    if (!res)
        return;
    res = A.point[res].ch[a[u]];
    answer += A.cnt[res];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        addblock(v, u, res);
    }
}
inline void addsolveblock(int u, int _fa)
{
    addblock(u, 0);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        addsolveblock(v, u);
    }
}
inline void mark(int u, int _fa)
{
    if (!f[u] && !g[u])
        return;
    ++A.dp[f[u]];
    ++B.dp[g[u]];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        mark(v, u);
    }
}
inline void addtree(int u, int _fa)
{
    A.clear(), B.clear();
    mark(u, _fa);
    A.dfs(1), B.dfs(1);
    for (int i = 1; i <= m; ++i)
        answer += (ll)A.dp[A.where[i]] * B.dp[B.where[m - i + 1]];
}
inline void deltree(int u, int _fa)
{
    A.clear(), B.clear();
    mark(u, _fa);
    A.dfs(1), B.dfs(1);
    for (int i = 1; i <= m; ++i)
        answer -= (ll)A.dp[A.where[i]] * B.dp[B.where[m - i + 1]];
}
inline void dfs2(int u, int _fa, int res)
{
    res = A.point[res].ch[a[u]];
    if (!res)
        return;
    answer -= A.cnt[res];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        dfs2(v, u, res);
    }
}
inline void dfs1(int u, int _fa, int res, int goal, int fagoal)
{
    res = A.calc(res, dep[_fa], a[u]);
    if (!res)
        return;
    dfs2(goal, fagoal, res);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        dfs1(v, u, res, goal, fagoal);
    }
}
inline void solve(int u)
{
    if (sum <= block)
    {
        addsolveblock(u, 0);
        vis[u] = true;
    }
    else
    {
        getroot(u, 0);
        u = root;
        f[u] = A.point[1].ch[a[u]];
        g[u] = B.point[1].ch[a[u]];
        dfs(u, 0);
        vis[u] = true;
        addtree(u, 0);
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (vis[v])
                continue;
            if (size[v] <= block)
                dfs1(v, u, A.point[1].ch[a[u]], v, u);
            else
                deltree(v, u);
        }
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (vis[v])
                continue;
            maxsize[root = 0] = sum = size[v];
            solve(v);
        }
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
        a[i] = str[i] - 'a';
    scanf("%s", str + 1);
    for (int i = 1; i <= m; ++i)
        A.str[i] = str[i];
    A.init();
    for (int i = 1; i <= m; ++i)
        B.str[m - i + 1] = str[i];
    B.init();
    maxsize[root = 0] = sum = n;
    block = (int)(2.3 * sqrt(m));
    f[0] = g[0] = 1;
    solve(1);
    printf("%lld\n", answer);
    return 0;
}