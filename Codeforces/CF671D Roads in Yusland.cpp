/**
 *    unicode: UTF-8
 *    name:    CF671D Roads in Yusland
 *    author:  whitepaperdog
 *    created: 2022.06.30 周四 16:55:55 (Asia/Shanghai)
 **/
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
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
constexpr int N = 3e5 + 5;
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
struct Tree
{
    int key, val;
    int tag;
    int ch[2];
    int dist;
    inline void add(int _val)
    {
        key += _val;
        tag += _val;
    }
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
int root[N], cnt;
inline void pushup(int x)
{
    if (tree[lc(x)].dist < tree[rc(x)].dist)
        swap(lc(x), rc(x));
    tree[x].dist = tree[rc(x)].dist + 1;
}
inline void pushdown(int x)
{
    if (tree[x].tag)
    {
        if (lc(x))
            tree[lc(x)].add(tree[x].tag);
        if (rc(x))
            tree[rc(x)].add(tree[x].tag);
        tree[x].tag = 0;
    }
}
inline int merge(int &x, int y)
{
    if (!x || !y)
        return x | y;
    pushdown(x), pushdown(y);
    if (tree[x].key > tree[y].key)
        swap(x, y);
    rc(x) = merge(rc(x), y);
    pushup(x);
    return x;
}
vector<pair<int, int>> g[N];
int dep[N];
ll answer;
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    for (auto v : g[u])
    {
        ++cnt;
        tree[cnt].key = v.first;
        tree[cnt].val = v.second;
        root[u] = merge(root[u], cnt);
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        root[u] = merge(root[u], root[v]);
    }
    while (root[u] && dep[tree[root[u]].val] >= dep[u])
        root[u] = merge(lc(root[u]), rc(root[u]));
    if (root[u])
    {
        answer += tree[root[u]].key;
        tree[root[u]].add(-tree[root[u]].key);
    }
    else if (u > 1)
    {
        printf("-1\n");
        exit(0);
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= m; ++i)
    {
        int x, y, c;
        read(x, y, c);
        g[x].push_back(make_pair(c, y));
    }
    dfs(1, 0);
    printf("%lld\n", answer);
    return 0;
}