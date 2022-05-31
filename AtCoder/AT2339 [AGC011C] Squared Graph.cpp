#include <bits/stdc++.h>
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
constexpr int N = 1e5 + 5, M = 4e5 + 5;
int n, m;
struct Edge
{
    int next, to;
} edge[M];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int vis[N];
bool exist;
inline void dfs(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (!vis[v])
        {
            vis[v] = 3 - vis[u];
            dfs(v);
        }
        else if (vis[v] != 3 - vis[u])
            exist = true;
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    int a = 0, b = 0, c = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (vis[i])
            continue;
        if (!head[i])
            ++c;
        else
        {
            exist = false;
            vis[i] = 1;
            dfs(i);
            if (exist)
                ++a;
            else
                ++b;
        }
    }
    printf("%lld\n", (ll)a * a + 2ll * (a + b) * b + (ll)(n - c + 1 + n) * c - c);
    return 0;
}