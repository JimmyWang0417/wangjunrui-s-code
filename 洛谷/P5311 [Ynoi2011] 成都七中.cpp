#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 1e5 + 5;
int n, m, a[N];
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
int sum, root, size[N], maxsize[N];
bool vis[N];
inline void getroot(int u, int _fa)
{
    size[u] = 1;
    maxsize[u] = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        getroot(v, u);
        size[u] += size[v];
        ckmax(maxsize[u], size[v]);
    }
    ckmax(maxsize[u], sum - size[u]);
    if (maxsize[root] > maxsize[u])
        root = u;
}
struct node
{
    int l, r, color;
    node(int _l = 0, int _r = 0, int _color = 0) : l(_l), r(_r), color(_color) {}
    inline bool operator<(const node &rhs) const
    {
        return r < rhs.r;
    }
};
vector<node> point[N];

node fa[N][25];
int cnt[N];

inline void dfs(int u, int _fa, int minn, int maxx)
{
    size[u] = 1;
    ++cnt[u];
    fa[u][cnt[u]] = node(minn, maxx, root);
    point[root].push_back(node(minn, maxx, a[u]));
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        dfs(v, u, min(minn, v), max(maxx, v));
        size[u] += size[v];
    }
}
inline void solve(int u)
{
    getroot(u, 0);
    u = root;
    root = u;
    dfs(u, 0, u, u);
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        maxsize[root = 0] = sum = size[v];
        solve(v);
    }
}
inline int findroot(int u, int l, int r)
{
    for (int i = 1; i < cnt[u]; ++i)
        if (l <= fa[u][i].l && fa[u][i].r <= r)
            return fa[u][i].color;
    return u;
}
struct Tree_array
{
    int c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            c[i] += val;
    }
    inline void update(int l, int r, int val)
    {
        update(l, val);
        update(r + 1, -val);
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
    inline int query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
    inline void clear(int pos)
    {
        for (int i = pos; i <= n && c[i]; i += lowbit(i))
            c[i] = 0;
    }
    inline void clear()
    {
        memset(c, 0, sizeof(c));
    }
} tree;
vector<node> q[N];
int las[N];
int answer[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    maxsize[root = 0] = sum = n;
    solve(1);
    for (int i = 1; i <= m; ++i)
    {
        int l, r, x;
        read(l, r, x);
        q[findroot(x, l, r)].push_back(node(l, r, i));
    }
    for (int i = 1; i <= n; ++i)
    {
        sort(point[i].begin(), point[i].end());
        sort(q[i].begin(), q[i].end());
        auto it = point[i].begin();
        for (auto u : q[i])
        {
            while (it != point[i].end() && it->r <= u.r)
            {
                if (las[it->color] < it->l)
                {
                    tree.update(las[it->color] + 1, it->l, 1);
                    las[it->color] = it->l;
                }
                ++it;
            }
            answer[u.color] = tree.query(u.l);
        }
        it = point[i].begin();
        while (it != point[i].end())
        {
            if (las[it->color])
            {
                tree.update(1, las[it->color], -1);
                las[it->color] = 0;
            }
            ++it;
        }
        // tree.clear();
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}