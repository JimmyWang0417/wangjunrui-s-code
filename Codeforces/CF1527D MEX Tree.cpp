#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 2e5 + 5;
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
int size[N];
int fa[N][25];
int dep[N];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    fa[u][0] = _fa;
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        size[u] += size[v];
    }
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
inline int getfa(int u, int k)
{
    for (int i = 0; i <= 20; ++i)
        if ((k >> i) & 1)
            u = fa[u][i];
    return u;
}
int n;
ll answer[N];
inline void work()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        ++u, ++v;
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    answer[1] = 0;
    ll sum = 1;
    for (int i = head[1]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        answer[1] += (ll)size[v] * sum;
        sum += size[v];
    }
    int l = 1, r = 1, sl = 0, sr = 0;
    for (int i = 2; i <= n; ++i)
    {
        int a = getlca(i, l), b = getlca(i, r);
        if (a == l && b == 1)
        {
            if (l == 1)
                sl = size[getfa(i, dep[i] - dep[1] - 1)];
            l = i;
        }
        else if (a == 1 && b == r)
        {

            if (r == 1)
                sr = size[getfa(i, dep[i] - dep[1] - 1)];
            r = i;
        }
        else if (a != i && b != i)
            break;
        if (l == 1)
            answer[i] = (ll)size[r] * (n - sr);
        else if (r == 1)
            answer[i] = (ll)size[l] * (n - sl);
        else
            answer[i] = (ll)size[l] * size[r];
    }
    printf("%lld", (ll)n * (n - 1) / 2 - answer[1]);
    for (int i = 2; i <= n + 1; ++i)
        printf(" %lld", answer[i - 1] - answer[i]);
    putchar('\n');
    memset(head, num_edge = 0, sizeof(head));
    memset(answer, 0, sizeof(answer));
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}