/**
 *    unicode: UTF-8
 *    name:    P8341 [AHOI2022] 回忆
 *    author:  wangjunrui
 *    created: 2022.08.25 周四 16:14:14 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
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
constexpr int N = 2e5 + 5;
int n, m;
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
int dep[N];
int mp[N];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
}
int a[N], b[N];
int up[N], minup[N];
inline void solve(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        solve(v, u);
        a[v] += mp[dep[u]];
        mp[dep[u]] = 0;
        if (dep[u] == minup[v])
        {
            ++a[v];
            minup[v] = 0;
        }
        if (minup[u] && minup[v])
        {
            if (minup[u] > minup[v])
                swap(minup[u], minup[v]);
            ++mp[minup[v]];
        }
        else
            minup[u] |= minup[v];
        if (a[u] < a[v])
        {
            swap(a[u], a[v]);
            swap(b[u], b[v]);
        }
        if (a[u] <= a[v] + b[v] * 2)
        {
            int w = a[u] + a[v] + b[v] * 2;
            a[u] = w & 1;
            b[u] += w >> 1;
        }
        else
        {
            a[u] -= a[v] + b[v] * 2;
            b[u] += a[v] + b[v] * 2;
        }
        a[v] = b[v] = minup[v] = 0;
    }
    if (up[u])
    {
        if (!minup[u])
        {
            minup[u] = up[u];
            if (a[u])
                --a[u];
            else if (b[u])
            {
                ++a[u];
                --b[u];
            }
        }
        else
            ckmin(minup[u], up[u]);
        up[u] = 0;
    }
}
signed main()
{
    int T = 1;
    read(T);
    while (T--)
    {
        read(n, m);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            read(u, v);
            add_edge(u, v);
            add_edge(v, u);
        }
        dfs(1, 0);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            read(u, v);
            if (!up[v])
                up[v] = dep[u];
            else
                ckmin(up[v], dep[u]);
        }
        solve(1, 0);
        printf("%d\n", a[1] + b[1]);
        a[1] = b[1] = minup[1] = 0;
        fill(head + 1, head + 1 + n, num_edge = 0);
    }
    return 0;
}