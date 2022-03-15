#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
template <typename T>
inline void read(T &x)
{
    x = 0;
    static char s = (char)getchar();
    static bool f = false;
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
int n, a[N];
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
int dfn[N], low[N], dfstime;
inline void dfs(int u, int _fa)
{
    dfn[u] = dfstime + 1;
    bool haveson = false;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        haveson = true;
    }
    if (!haveson)
        ++dfstime;
    low[u] = dfstime;
}
struct node
{
    int u, v, w, id;
    inline bool operator<(const node &rhs) const
    {
        return w < rhs.w;
    }
} b[N];
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
bool answer[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
    {
        b[i].u = dfn[i];
        b[i].v = low[i] + 1;
        b[i].w = a[i];
        b[i].id = i;
    }
    sort(b + 1, b + 1 + n);
    ll res = 0;
    int cnt = 0;
    for (int l = 1, r; l <= n; l = r)
    {
        r = l + 1;
        while (r <= n && b[l].w == b[r].w)
            ++r;
        for (int i = l; i < r; ++i)
            if (find(b[i].u) != find(b[i].v))
            {
                answer[b[i].id] = true;
                ++cnt;
            }
        for (int i = l; i < r; ++i)
        {
            int u = find(b[i].u), v = find(b[i].v);
            if (u != v)
            {
                res += b[i].w;
                fa[u] = v;
            }
        }
    }
    printf("%lld %d\n", res, cnt);
    for (int i = 1; i <= n; ++i)
        if (answer[i])
            printf("%d ", i);
    putchar('\n');
    return 0;
}