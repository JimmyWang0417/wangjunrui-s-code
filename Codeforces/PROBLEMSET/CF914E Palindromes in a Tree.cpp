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
const int N = 2e5 + 5, M = 1e7 + 5;
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
int n;
char str[N];
int maxsize[N], size[N], sum, root;
bool vis[N];
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
        maxsize[u] = max(maxsize[u], size[v]);
    }
    maxsize[u] = max(maxsize[u], sum - size[u]);
    if (maxsize[root] > maxsize[u])
        root = u;
}
inline void getsize(int u, int _fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        getsize(v, u);
        size[u] += size[v];
    }
}
int mp[M];
inline void dfs(int u, int _fa, int S, int val)
{
    S ^= (1 << (str[u] - 'a'));
    mp[S] += val;
    //	printf("%d\n",S);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        dfs(v, u, S, val);
    }
}
ll answer[N];
inline ll calc(int u, int _fa, int S)
{
    S ^= (1 << (str[u] - 'a'));
    ll res = mp[S];
    for (int i = 0; i <= 't' - 'a'; ++i)
        res += mp[S ^ (1 << i)];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        res += calc(v, u, S);
    }
    answer[u] += res;
    return res;
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    vis[u] = true;
    getsize(u, 0);
    dfs(u, 0, 0, 1);
    ll res = mp[0];
    for (int i = 0; i <= 't' - 'a'; ++i)
        res += mp[1 << i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        dfs(v, u, 1 << (str[u] - 'a'), -1);
        res += calc(v, u, 0);
        dfs(v, u, 1 << (str[u] - 'a'), 1);
    }
    answer[u] += res / 2;
    dfs(u, 0, 0, -1);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = size[v];
        solve(v);
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
    maxsize[root = 0] = sum = n;
    solve(1);
    for (int i = 1; i <= n; ++i)
        printf("%lld ", answer[i] + 1);
    putchar('\n');
    return 0;
}
