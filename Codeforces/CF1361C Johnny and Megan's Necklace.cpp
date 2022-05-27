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
const int N = 2e6 + 5;
int n, a[N], b[N];
int deg[N];
int fa[N];
struct Edge
{
    int next, to;
    bool vis;
} edge[N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int st[N], top;
inline void dfs(int u)
{
    for (int &i = head[u]; i; i = edge[i].next)
    {
        if (edge[i].vis)
            continue;
        edge[i].vis = edge[i ^ 1].vis = true;
        int &v = edge[i].to;
        dfs(v);
    }
    st[++top] = u;
}
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    fa[x] = y;
}
inline bool check(int k)
{
    int S = (1 << k) - 1;
    for (int i = 1; i <= n; ++i)
    {
        int u = (a[i] & S) + n + 1;
        merge(u, i);
        ++deg[u], ++deg[i];

        u = (b[i] & S) + n + 1;
        merge(u, i);
        ++deg[u], ++deg[i];
    }
    for (int i = 1; i <= n; ++i)
        if (find(i) != find(1))
            return false;
    for (int i = 1; i <= 2 * n + S + 1; ++i)
        if (deg[i] & 1)
            return false;
    for (int i = 1; i <= n; ++i)
    {
        int u = (a[i] & S) + n + 1;
        add_edge(u, i), add_edge(i, u);

        u = (b[i] & S) + n + 1;
        add_edge(u, i), add_edge(i, u);
    }
    return true;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i], b[i]);
    for (int k = 20; k >= 0; --k)
    {
        if (check(k))
        {
            dfs(1);
            printf("%d\n", k);
            for (int i = 1; i < top; ++i)
                if (st[i] <= n)
                {
                    int s = (st[i + 1] - (n + 1)), id = st[i];
                    if ((a[id] & ((1 << k) - 1)) == s)
                        printf("%d %d ", id * 2, id * 2 - 1);
                    else
                        printf("%d %d ", id * 2 - 1, id * 2);
                }
            return 0;
        }
        memset(fa, 0, sizeof(fa));
        memset(deg, 0, sizeof(deg));
    }
    return 0;
}