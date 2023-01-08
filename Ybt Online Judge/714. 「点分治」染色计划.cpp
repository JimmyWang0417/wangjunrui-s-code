#include <cstdio>
#include <list>
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
constexpr int N = 2e5 + 5;
int n, m, a[N];
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
list<int> g[N];
int size[N], maxsize[N], root, sum;
bool vis[N];
inline void getroot(int u, int _fa)
{
    size[u] = 1;
    maxsize[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        getroot(v, u);
        size[u] += size[v];
        ckmax(maxsize[u], size[v]);
    }
    ckmax(maxsize[u], sum - size[u]);
    if (maxsize[u] < maxsize[root])
        root = u;
}
int fa[N];
bool exist[N];
int st[N], top;
inline void add(int u, int _fa)
{
    st[++top] = u;
    size[u] = 1;
    fa[u] = _fa;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        add(v, u);
        size[u] += size[v];
    }
}
int answer;
int q[N], rnmtq[N];
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    add(u, 0);
    int tail = 0;
    q[++tail] = a[u];
    rnmtq[a[u]] = true;
    exist[u] = true;
    bool flag = false;
    for (int i = 1; i <= tail; ++i)
    {
        int color = q[i];
        for (auto v : g[color])
        {
            if (exist[v])
                continue;
            if (!fa[v])
            {
                flag = true;
                break;
            }
            exist[v] = true;
            while (fa[v] && !exist[fa[v]])
            {
                v = fa[v];
                exist[v] = true;
                if (!rnmtq[a[v]])
                {
                    rnmtq[a[v]] = true;
                    q[++tail] = a[v];
                }
            }
        }
        if (flag)
            break;
    }
    for (int i = 1; i <= tail; ++i)
        rnmtq[q[i]] = false;
    while (top)
    {
        fa[st[top]] = exist[st[top]] = 0;
        --top;
    }
    if (!flag)
        ckmin(answer, tail);
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
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        g[a[i]].push_back(i);
    }
    answer = m;
    maxsize[root = 0] = sum = n;
    solve(1);
    printf("%d\n", answer - 1);
    return 0;
}