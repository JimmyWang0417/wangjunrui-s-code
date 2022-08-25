/**
 *    unicode: UTF-8
 *    name:    P5332 [JSOI2019]精准预测
 *    author:  wangjunrui
 *    created: 2022.08.19 周五 00:22:57 (Asia/Shanghai)
 **/
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>
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
constexpr int N = 5e4 + 5;
constexpr int M = 3e5 + 5;
constexpr int S = 2.7e4;
int T, n, m;
struct node
{
    int opt, t, x, y;
} a[N * 2];
bitset<S> status[M];
vector<int> g[N];
struct Edge
{
    int next, to;
} edge[M * 4];
int head[M], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
bitset<N> dead;
bitset<M> vis;
int sum[N];
inline void dfs(int u)
{
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!vis[v])
            dfs(v);
        status[u] |= status[v];
    }
}
int answer[N];
signed main()
{
    read(T, n, m);
    for (int i = 1; i <= n; ++i)
        g[i].push_back(T + 1);
    for (int i = 1; i <= m; ++i)
    {
        read(a[i].opt, a[i].t, a[i].x, a[i].y);
        g[a[i].x].push_back(a[i].t);
    }
    auto calc0 = [](int x, int y)
    {
        return sum[x - 1] + y;
    };
    auto calc1 = [](int x, int y)
    {
        return sum[x - 1] + y + sum[n];
    };
    for (int i = 1; i <= n; ++i)
    {
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
        sum[i] = sum[i - 1] + (int)g[i].size();
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < (int)g[i].size() - 1; ++j)
        {
            add_edge(calc0(i, j + 1), calc0(i, j));
            add_edge(calc1(i, j), calc1(i, j + 1));
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        auto [opt, t, x, y] = a[i];
        if (!a[i].opt)
        {
            int u = (int)(lower_bound(g[x].begin(), g[x].end(), t) - g[x].begin()),
                v = (int)(upper_bound(g[y].begin(), g[y].end(), t) - g[y].begin());
            add_edge(calc0(y, v), calc0(x, u));
            add_edge(calc1(x, u), calc1(y, v));
        }
        else
        {
            int u = (int)(lower_bound(g[x].begin(), g[x].end(), t) - g[x].begin()),
                v = (int)(lower_bound(g[y].begin(), g[y].end(), t) - g[y].begin());
            add_edge(calc0(x, u), calc1(y, v));
            add_edge(calc0(y, v), calc1(x, u));
        }
    }
    bitset<S> cur;
    for (int l = 1, r; l <= n; l = r + 1)
    {
        r = min(l + S - 1, n);
        for (int i = l; i <= r; ++i)
            status[calc1(i, (int)g[i].size() - 1)].set(i - l);
        for (int i = 0; i < 2 * sum[n]; ++i)
            if (!vis[i])
                dfs(i);
        for (int i = l; i <= r; ++i)
            if (status[calc0(i, (int)g[i].size() - 1)][i - l])
            {
                dead.set(i);
                cur.set(i - l);
            }
        for (int i = 1; i <= n; ++i)
            answer[i] += (r - l + 1) - (int)(cur | status[calc0(i, (int)g[i].size() - 1)]).count();
        for (int i = 0; i < 2 * sum[n]; ++i)
            status[i].reset();
        cur.reset();
        vis.reset();
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", dead[i] ? 0 : answer[i] - 1);
    putchar('\n');
    return 0;
}