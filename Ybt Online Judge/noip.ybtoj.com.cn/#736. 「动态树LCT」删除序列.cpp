// Problem: F. Matches Are Not a Child's Play
// Contest: Codeforces - Codeforces Round #545 (Div. 1)
// URL: http://codeforces.com/problemset/problem/1137/F
// Memory Limit: 512 MB
// Time Limit: 4000 ms
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
constexpr int N = 4e5 + 5;
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
struct Tree_array
{
    int tot, c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= tot; i += lowbit(i))
            c[i] += val;
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
} t;
struct Tree
{
    int ch[2], fa;
    int color;
    int size;
    bool rev;
    inline void reverse()
    {
        swap(ch[0], ch[1]);
        rev ^= 1;
    }
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
    tree[x].size = tree[lc(x)].size + tree[rc(x)].size + 1;
}
inline void pushdown(int x)
{
    if (tree[x].rev)
    {
        if (lc(x))
            tree[lc(x)].reverse();
        if (rc(x))
            tree[rc(x)].reverse();
        tree[x].rev = false;
    }
    if (lc(x))
        tree[lc(x)].color = tree[x].color;
    if (rc(x))
        tree[rc(x)].color = tree[x].color;
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
int st[N];
inline void splay(int x)
{
    int top;
    st[top = 1] = x;
    for (int y = x; nroot(y); y = fa(y))
        st[++top] = fa(y);
    while (top)
        pushdown(st[top--]);
    while (nroot(x))
    {
        if (nroot(fa(x)))
            rotate(check(fa(x)) == check(x) ? fa(x) : x);
        rotate(x);
    }
}
inline void access(int x, int nowcolor)
{
    for (int y = 0; x; x = fa(y = x))
    {
        splay(x);
        rc(x) = 0;
        pushup(x);
        t.update(tree[x].color, -tree[x].size);
        t.update(nowcolor, tree[x].size);
        rc(x) = y;
        pushup(x);
    }
}
int color;
inline void makeroot(int x)
{
    access(x, ++color);
    splay(x);
    tree[x].reverse();
    tree[x].color = color;
}
inline int query(int x)
{
    splay(x);
    return t.query(tree[x].color) - tree[lc(x)].size;
}
inline void dfs(int u, int _fa)
{
    tree[u].color = u;
    tree[u].size = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        tree[v].fa = u;
        if (tree[v].color > tree[u].color)
        {
            tree[u].color = tree[v].color;
            rc(u) = v;
            pushup(u);
        }
    }
    t.update(tree[u].color, 1);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("delete.in", "r", stdin);
    freopen("delete.out", "w", stdout);
#endif
    read(n, m);
    t.tot = n + m;
    color = n;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(n, 0);
    for (int i = 1; i <= m; ++i)
    {
        char opt[10];
        scanf("%s", opt);
        if (opt[0] == '1')
        {
            int u;
            read(u);
            makeroot(u);
        }
        else if (opt[0] == '2')
        {
            int u;
            read(u);
            printf("%d\n", query(u));
        }
        else
        {
            int u, v;
            read(u, v);
            printf("%d\n", query(u) < query(v) ? u : v);
        }
    }
    return 0;
}
