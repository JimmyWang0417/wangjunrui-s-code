/**
 *    unicode: UTF-8
 *    name:    P5292 [HNOI2019]校园旅行
 *    author:  wangjunrui
 *    created: 2022.08.08 周一 15:50:30 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
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
constexpr int N = 5005, M = 5e5 + 5;
int n, m, q;
char str[N];
struct node
{
    node(int _u = 0, int _v = 0) : u(_u), v(_v) {}
    int u, v;
} a[M];
struct union_set
{
    int fa[N];
    inline int find(int x)
    {
        return !fa[x] ? x : find(fa[x]);
    }
    inline bool unionn(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        fa[x] = y;
        return true;
    }
} fa, fb;
struct Edge
{
    int next, to;
} edge[M * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
bool exist;
int vis[N];
inline void dfs(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!vis[v])
        {
            vis[v] = 3 - vis[u];
            dfs(v);
        }
        else if (vis[u] == vis[v])
            exist = true;
    }
}
int st[N], top;
bool dis[N][N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n, m, q);
    scanf("%s", str + 1);
    for (int i = 1; i <= m; ++i)
    {
        read(a[i].u, a[i].v);
        if (str[a[i].u] == str[a[i].v])
        {
            add_edge(a[i].u, a[i].v);
            add_edge(a[i].v, a[i].u);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (vis[i])
            continue;
        dfs(i);
        if (exist)
        {
            st[++top] = i;
            exist = false;
        }
    }
    fill(head + 1, head + 1 + n, num_edge = 0);
    queue<node> que;
    for (int i = 1; i <= m; ++i)
    {
        int u = a[i].u, v = a[i].v;
        if (str[u] == str[v])
        {
            if (fa.unionn(u, v))
            {
                add_edge(u, v);
                add_edge(v, u);
                dis[u][v] = dis[v][u] = true;
                que.emplace(u, v);
            }
        }
        else
        {
            if (fb.unionn(u, v))
            {
                add_edge(u, v);
                add_edge(v, u);
            }
        }
    }
    while (top)
    {
        add_edge(st[top], st[top]);
        --top;
    }
    for (int i = 1; i <= n; ++i)
    {
        dis[i][i] = true;
        que.emplace(i, i);
    }
    while (!que.empty())
    {
        auto [ua, ub] = que.front();
        que.pop();
        for (int i = head[ua]; i; i = edge[i].next)
        {
            int va = edge[i].to;
            for (int j = head[ub]; j; j = edge[j].next)
            {
                int vb = edge[j].to;
                if (str[va] != str[vb] || dis[va][vb])
                    continue;
                dis[va][vb] = dis[vb][va] = true;
                que.emplace(va, vb);
            }
        }
    }
    for (int i = 1; i <= q; ++i)
    {
        int x, y;
        read(x, y);
        puts(dis[x][y] ? "YES" : "NO");
    }
    return 0;
}