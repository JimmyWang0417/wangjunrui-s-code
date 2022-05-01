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
constexpr int N = 1e5 + 5;
int n, m;
int a[N];
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
struct LCT
{
    struct Tree
    {
        int ch[2], fa;
        int fakesize, size;
    } tree[N];
#define fa(x) tree[x].fa
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
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
            tree[x].fakesize += tree[rc(x)].size;
            tree[x].fakesize -= tree[rc(x) = y].size;
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
    inline void link(int x)
    {
        int y = fa[x];
        access(y);
        splay(y);
        splay(x);
        fa(x) = y;
        tree[y].fakesize += tree[x].size;
        pushup(y);
    }
    inline void cut(int x)
    {
        access(x);
        splay(x);
        lc(x) = fa(lc(x)) = 0;
        pushup(x);
    }
    inline int query(int x)
    {
        int v = findroot(x);
        splay(v);
        return tree[rc(v)].size;
    }
} lct[2];
signed main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n + 1; ++i)
        lct[0].tree[i].size = lct[1].tree[i].size = 1;
    dfs(1, n + 1);
    for (int i = 1; i <= n; ++i)
        lct[0].link(i);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int opt, u;
        read(opt, u);
        if (opt)
        {
            lct[a[u]].cut(u);
            lct[a[u] ^= 1].link(u);
        }
        else
            printf("%d\n", lct[a[u]].query(u));
    }
    return 0;
}