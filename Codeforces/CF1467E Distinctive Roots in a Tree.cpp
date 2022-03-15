// Problem: E. Distinctive Roots in a Tree
// Contest: Codeforces - Codeforces Round #695 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1467/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
int p[N], tot;
int cnt[N], mp[N];
int diff[N];
int dfn[N], low[N], dfstime;
inline void dfs(int u, int _fa)
{
    dfn[u] = ++dfstime;
    int lascnt = mp[a[u]];
    ++mp[a[u]];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        int las = mp[a[u]];
        dfs(v, u);
        if (mp[a[u]] > las)
        {
            ++diff[1];
            --diff[dfn[v]];
            ++diff[low[v] + 1];
        }
    }
    low[u] = dfstime;
    if (mp[a[u]] - lascnt < cnt[a[u]])
    {
        ++diff[dfn[u]];
        --diff[low[u] + 1];
    }
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[++tot] = a[i];
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    for (int i = 1; i <= n; ++i)
        ++cnt[a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p)];
    dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        diff[i] += diff[i - 1];
        if (diff[i] == 0)
            ++ans;
    }
    printf("%d\n", ans);
    return 0;
}