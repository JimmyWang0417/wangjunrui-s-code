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
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int p[N], tot;
bool vis[N];
int maxx[2];
int cnt = 0;
inline void dfs(int u, int lasedge)
{
    vis[u] = true;
    if (u > maxx[0])
    {
        maxx[1] = maxx[0];
        maxx[0] = u;
    }
    else if (u > maxx[1])
        maxx[1] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (i == (lasedge ^ 1))
            continue;
        if (vis[v])
            ++cnt;
        else
            dfs(v, i);
    }
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i], b[i]);
        p[++tot] = a[i], p[++tot] = b[i];
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
        b[i] = (int)(lower_bound(p + 1, p + 1 + tot, b[i]) - p);
        add_edge(a[i], b[i]);
        add_edge(b[i], a[i]);
    }
    int res = 0;
    for (int i = 1; i <= tot; ++i)
    {
        if (vis[i])
            continue;
        maxx[0] = maxx[1] = cnt = 0;
        dfs(i, 0);
        cnt /= 2;
        if (cnt > 1)
        {
            printf("-1\n");
            return 0;
        }
        else if (cnt == 1)
            ckmax(res, maxx[0]);
        else
            ckmax(res, maxx[1]);
    }
    printf("%d\n", p[res]);
    return 0;
}