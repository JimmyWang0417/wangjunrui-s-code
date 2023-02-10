#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 2505;
int n;
char str[N];
bitset<N> vis;
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
bitset<26> g[N];
int dp[N];
int belong[N];
inline bool find(int u, int fa)
{
    for (int i = head[fa]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || !g[v][u])
            continue;
        vis[v] = true;
        if (belong[v] == -1 || find(belong[v], fa))
        {
            belong[v] = u;
            return true;
        }
    }
    return false;
}
inline bool tryfind(int u, int fa)
{
    for (int i = head[fa]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || !g[v][u])
            continue;
        vis[v] = true;
        if (belong[v] == -1 || tryfind(belong[v], fa))
            return true;
    }
    return false;
}
inline void dfs(int u)
{
    dp[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
        dp[u] += dp[v];
    }
    for (int i = 0; i < 26; ++i)
        if (g[u][i])
        {
            vis.reset();
            dp[u] += 1 - find(i, u);
        }
    for (int i = head[u]; i; i = edge[i].to)
    {
        int &v = edge[i].to;
        vis.reset();
        vis[v] = true;
        if (belong[v] == -1 || tryfind(belong[v], u))
            g[u] |= g[v];
    }
}
int fa[N];
int st[N], top;
signed main()
{
    freopen("expr.in", "r", stdin), freopen("expr.out", "w", stdout);
    scanf("%s", str + 1);
    n = (int)(strlen(str + 1));
    memset(belong, -1, sizeof(belong));
    for (int i = 1; i <= n; ++i)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            st[++top] = i;
        }
        else
        {
            fa[st[top]] = fa[st[top - 1]] = i;
            st[--top] = i;
        }
    }
    for (int i = 1; i < n; ++i)
        while (str[fa[i]] == str[fa[fa[i]]])
        {
            vis[fa[i]] = true;
            fa[i] = fa[fa[i]];
        }
    //	printf("nmsl\n");
    for (int i = 1; i < n; ++i)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            g[fa[i]][str[i] - 'a'] = true;
        else if (!vis[i])
            add_edge(fa[i], i);
    }
    dfs(n);
    printf("%d\n", dp[n]);
    return 0;
}
