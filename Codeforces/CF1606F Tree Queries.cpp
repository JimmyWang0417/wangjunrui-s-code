#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int BLOCK = (int)sqrt(N) + 10;
int n, q;
int block, num;
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
int f[N][BLOCK];
int h[BLOCK];
int size[N];
inline void dfs1(int u, int _fa)
{
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        if (v == _fa)
            continue;
        dfs1(v, u);
        for (int i = 0; i <= block; ++i)
            f[u][i] += max(1, f[v][i] - i);
    }
}
inline void dfs2(int u, int _fa)
{
    size[u] = 1;
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        if (v == _fa)
            continue;
        dfs2(v, u);
        memcpy(h, f[u], sizeof(f[u]));
        memset(f[u], 0, sizeof(f[u]));
        for (int i = 0; i < size[u] && i < num; ++i)
        {
            ckmax(f[u][i], h[i] + 1);
            for (int j = 0; i + j < num && j < size[v]; ++j)
                ckmax(f[u][i + j + 1], h[i] + f[v][j]);
        }
        size[u] += size[v];
    }
}
list<pair<pair<int, int>, int>> cf;
int answer[N];
signed main()
{
    read(n);
    block = (int)sqrt(n);
    num = (n - 1) / block + 1 + 5;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(1, 0);
    read(q);
    for (int now = 1; now <= q; ++now)
    {
        int u, k;
        read(u, k);
        if (k <= block)
            answer[now] = f[u][k];
        else
            cf.push_back(make_pair(make_pair(u, k), now));
    }
    memset(f, 0, sizeof(f));
    dfs2(1, 0);
    for (auto v : cf)
    {
        int u = v.first.first, k = v.first.second, id = v.second;
        int &res = answer[id];
        for (int i = 0; i < num; ++i)
            ckmax(res, f[u][i] - i * k);
    }
    for (int i = 1; i <= q; ++i)
        printf("%d\n", answer[i]);
    return 0;
}