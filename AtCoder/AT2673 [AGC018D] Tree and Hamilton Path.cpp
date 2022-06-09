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
constexpr int N = 1e5 + 5;
int n;
struct Edge
{
    int next, to, dis;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int sze[N], maxsize[N];
int root, opproot;
ll answer;
inline void dfs(int u, int _fa)
{
    sze[u] = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        sze[u] += sze[v];
        ckmax(maxsize[u], sze[v]);
        answer += (ll)min(sze[v], n - sze[v]) * edge[i].dis;
    }
    ckmax(maxsize[u], n - sze[u]);
    if (maxsize[u] < maxsize[root])
    {
        root = u;
        opproot = 0;
    }
    else if (maxsize[u] == maxsize[root])
        opproot = u;
}
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    maxsize[0] = n;
    dfs(1, 0);
    if (!opproot)
    {
        int res = INT_MAX;
        for (int i = head[root]; i; i = edge[i].next)
            ckmin(res, edge[i].dis);
        printf("%lld\n", answer * 2 - res);
    }
    else
    {
        for (int i = head[root]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (v == opproot)
            {
                printf("%lld\n", answer * 2 - edge[i].dis);
                break;
            }
        }
    }
    return 0;
}
