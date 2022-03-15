#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
using namespace std;
const int N = 4e6 + 5;
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
int deg[N];
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int n, m, a[N];
struct SAM
{
    int ch[10], fa, len;
} point[N];
int tot = 1, las;
inline int insert(int c)
{
    int p = las, np = ++tot;
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
    return np;
}
inline void dfs(int u, int _fa)
{
    int id = insert(a[u]);
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        las = id;
        dfs(v, u);
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
        ++deg[u], ++deg[v];
    }
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1)
        {
            las = 1;
            dfs(i, 0);
        }
    ll ans = 0;
    for (int i = 2; i <= tot; ++i)
        ans += point[i].len - point[point[i].fa].len;
    printf("%lld\n", ans);
    return 0;
}