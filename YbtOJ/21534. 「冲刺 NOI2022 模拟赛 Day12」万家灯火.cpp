#include <cstdio>
#include <vector>
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
constexpr int N = 1e5 + 5;
int n, m;
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
int f[N][20];
#define fa(u) f[u][0]
inline void dfs(int u, int _fa)
{
    f[u][0] = _fa;
    for (int i = 0; i < 17; ++i)
        f[u][i + 1] = f[f[u][i]][i];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
}
int mp[N];
inline int jump(int u, int k)
{
    for (int i = 17; i >= 0; --i)
        if ((k >> i) & 1)
            u = f[u][i];
    return u;
}
struct tree_array
{
    int n;
    vector<int> c;
    inline void init(int _n)
    {
        n = _n + 1;
        c.resize(n + 5);
    }
    inline void update(int pos, int val)
    {
        for (int i = pos + 1; i <= n; i += lowbit(i))
            c[i] += val;
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = min(pos + 1, n); i >= 1; i -= lowbit(i))
            res += c[i];
        return res;
    }
} tree1[N], tree2[N];
int size[N], maxsize[N], root, sum;
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
        ckmax(maxsize[u], size[v]);
    }
    ckmax(maxsize[u], sum - size[u]);
    if (maxsize[root] > maxsize[u])
        root = u;
}
int dist[N][25], fa[N][25], cnt[N];
inline void getinfo(int u, int _fa, int dis)
{
    size[u] = 1;
    ++cnt[u];
    dist[u][cnt[u]] = dis, fa[u][cnt[u]] = root;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa || vis[v])
            continue;
        getinfo(v, u, dis + 1);
        size[u] += size[v];
    }
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    getinfo(u, 0, 0);
    tree1[u].init(sum / 2 + 1), tree2[u].init(sum);
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = size[v];
        solve(v);
    }
}
inline void add(int u, int val)
{
    tree1[u].update(0, val);
    for (int i = cnt[u] - 1; i >= 1; --i)
    {
        tree1[fa[u][i]].update(dist[u][i], val);
        tree2[fa[u][i + 1]].update(dist[u][i], val);
    }
}
inline void modify(int u)
{
    if (!a[u])
    {
        a[u] = true;
        add(u, -mp[u]);
        if (fa(u))
        {
            ++mp[fa(u)];
            if (!a[fa(u)])
                add(fa(u), 1);
        }
    }
    else
    {
        a[u] = false;
        add(u, mp[u]);
        if (fa[u])
        {
            --mp[fa(u)];
            if (!a[fa(u)])
                add(fa(u), -1);
        }
    }
}
inline int query(int u, int dis)
{
    --dis;
    int res = tree1[u].query(dis);
    for (int i = cnt[u] - 1; i >= 1; --i)
    {
        int now = dis - dist[u][i];
        res += tree1[fa[u][i]].query(now) - tree2[fa[u][i + 1]].query(now);
    }
    int v = jump(u, dis);
    if (v && v != 1)
    {
        if (a[v] && !a[fa(v)])
            ++res;
        v = fa(v);
    }
    else
        v = 1;
    if (v && a[v])
        ++res;
    if (a[u])
    {
        res += mp[u];
        if (!a[fa(u)])
            --res;
    }
    return res;
}
char str[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("lights.in", "r", stdin);
    freopen("lights.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        read(x, y);
        add_edge(x, y);
        add_edge(y, x);
    }
    dfs(1, 0);
    maxsize[root = 0] = sum = n;
    solve(1);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
        if (str[i] == '1')
            modify(i);
    for (int i = 1; i <= m; ++i)
    {
        int opt;
        read(opt);
        if (opt == 1)
        {
            int u;
            read(u);
            modify(u);
        }
        else
        {
            int u, v;
            read(u, v);
            printf("%d\n", query(u, v));
        }
    }
    return 0;
}
