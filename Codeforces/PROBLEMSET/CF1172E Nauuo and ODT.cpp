#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(x) (x & (-x))
template <typename tree>
inline void read(tree &x)
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
template <typename tree, typename... T1>
inline void read(tree &x, T1 &...x1)
{
    read(x);
    read(x1...);
}
template <typename tree>
inline void ckmin(tree &x, tree y)
{
    if (x > y)
        x = y;
}
template <typename tree>
inline void ckmax(tree &x, tree y)
{
    if (x < y)
        x = y;
}
using namespace std;
constexpr int N = 4e5 + 5;
int n, m, a[N];
bool exist[N];
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
int fa[N];
inline void dfs(int u, int _fa)
{
    fa[u] = _fa;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
}
struct Tree
{
    int ch[2], fa;
    int fakesize, size;
    ll fakesize2;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
inline bool check(int x)
{
    return rc(fa(x)) == x;
}
inline bool nroot(int x)
{
    return lc(fa(x)) == x || rc(fa(x)) == x;
}
inline void pushup(int x)
{
    tree[x].size = tree[lc(x)].size + tree[rc(x)].size + tree[x].fakesize + 1;
}
inline void rotate(int x)
{
    int y = fa(x), z = fa(y), k = check(x), w = tree[x].ch[k ^ 1];

    if (nroot(y))
        tree[z].ch[check(y)] = x;
    fa(x) = z;

    tree[x].ch[k ^ 1] = y;
    fa(y) = x;

    tree[y].ch[k] = w;
    if (w)
        fa(w) = y;

    pushup(y), pushup(x);
}
inline void splay(int x)
{
    while (nroot(x))
    {
        if (nroot(fa(x)))
            rotate(check(x) == check(fa(x)) ? fa(x) : x);
        rotate(x);
    }
}
inline void access(int x)
{
    for (int y = 0; x; x = fa(y = x))
    {
        splay(x);
        tree[x].fakesize += tree[rc(x)].size - tree[y].size;
        tree[x].fakesize2 += (ll)tree[rc(x)].size * tree[rc(x)].size - (ll)tree[y].size * tree[y].size;
        rc(x) = y;
        pushup(x);
    }
}
inline int findroot(int x)
{
    access(x);
    splay(x);
    while (lc(x))
        x = lc(x);
    splay(x);
    return x;
}

inline ll link(int x)
{
    int y = fa[x], z = findroot(y);
    access(x);
    splay(z);
    ll res = tree[x].fakesize2 + (ll)tree[rc(z)].size * tree[rc(z)].size;
    splay(y);
    fa(x) = y;
    tree[y].fakesize += tree[x].size;
    tree[y].fakesize2 += (ll)tree[x].size * tree[x].size;
    pushup(y);
    access(x);
    splay(z);
    return (ll)tree[rc(z)].size * tree[rc(z)].size - res;
}
inline ll cut(int x)
{
    int z = findroot(x);
    splay(z);
    ll res = tree[x].fakesize2 - (ll)tree[rc(z)].size * tree[rc(z)].size;
    splay(x);
    lc(x) = fa(lc(x)) = 0;
    pushup(x);
    splay(z);
    return (ll)tree[rc(z)].size * tree[rc(z)].size + res;
}
vector<pair<int, int>> g[N];
ll answer[N];
inline void solve(int id)
{
    for (auto u : g[id])
    {
        int x = u.first;
        answer[u.second] -= exist[x] ? cut(x) : link(x);
        exist[x] ^= 1;
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        g[a[i]].emplace_back(i, 0);
        exist[i] = true;
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n + 1; ++i)
        pushup(i);
    dfs(1, n + 1);
    for (int i = 1; i <= n; ++i)
        link(i);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        g[a[x]].emplace_back(x, i);
        g[a[x] = y].emplace_back(x, i);
    }
    for (int i = 1; i <= n; ++i)
        g[a[i]].emplace_back(i, m + 1);
    for (int i = 1; i <= n; ++i)
        solve(i);
    for (int i = 1; i <= m; ++i)
        answer[i] += answer[i - 1];
    for (int i = 0; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}