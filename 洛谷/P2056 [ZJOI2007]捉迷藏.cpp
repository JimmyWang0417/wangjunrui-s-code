#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
template <typename T>
inline void read(T &x)
{
    x = 0;
    static char s = (char)getchar();
    static bool f = false;
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
int fa[N][25], dis[N][25], cnt[N];
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
inline void dfs(int u, int _fa, int d)
{
    size[u] = 1;
    ++cnt[u];
    dis[u][cnt[u]] = d, fa[u][cnt[u]] = root;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v] || v == _fa)
            continue;
        dfs(v, u, d + 1);
        size[u] += size[v];
    }
}
inline void solve(int u)
{
    getroot(u, 0);
    u=root;
    dfs(u, 0, 0);
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
struct node
{
    priority_queue<int> addq, delq;
    inline int size()
    {
        return (int)(addq.size() - delq.size());
    }
    inline void add(int val)
    {
        addq.push(val);
    }
    inline void del(int val)
    {
        delq.push(val);
    }
    inline int top()
    {
        while (!delq.empty() && addq.top() == delq.top())
        {
            addq.pop();
            delq.pop();
        }
        return addq.top();
    }
    inline int calc()
    {
        while (!addq.empty() && !delq.empty() && addq.top() == delq.top())
        {
            addq.pop();
            delq.pop();
        }
        int x = addq.top();
        addq.pop();
        while (!addq.empty() && !delq.empty() && addq.top() == delq.top())
        {
            addq.pop();
            delq.pop();
        }
        int res = x + addq.top();
        addq.push(x);
        return res;
    }
} tree1[N], tree2[N], all;
inline void add(int u)
{
    if (tree1[u].size() >= 2)
        all.add(tree1[u].calc());
}
inline void del(int u)
{
    if (tree1[u].size() >= 2)
        all.del(tree1[u].calc());
}
inline void turnon(int u)
{
    del(u);
    tree1[u].del(0);
    add(u);
    for (int i = cnt[u] - 1; i >= 1; --i)
    {
        del(fa[u][i]);
        tree1[fa[u][i]].del(tree2[fa[u][i + 1]].top());
        tree2[fa[u][i + 1]].del(dis[u][i]);
        if (tree2[fa[u][i + 1]].size())
            tree1[fa[u][i]].add(tree2[fa[u][i + 1]].top());
        add(fa[u][i]);
    }
}
inline void turnoff(int u)
{
    del(u);
    tree1[u].add(0);
    add(u);
    for (int i = cnt[u] - 1; i >= 1; --i)
    {
        del(fa[u][i]);
        if (tree2[fa[u][i + 1]].size())
            tree1[fa[u][i]].del(tree2[fa[u][i + 1]].top());
        tree2[fa[u][i + 1]].add(dis[u][i]);
        tree1[fa[u][i]].add(tree2[fa[u][i + 1]].top());
        add(fa[u][i]);
    }
}
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
    maxsize[root = 0] = sum = n;
    solve(1);
    int tot = n;
    for (int i = 1; i <= n; ++i)
        turnoff(i);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        char opt[10];
        scanf("%s", opt);
        if (opt[0] == 'C')
        {
            int x;
            read(x);
            if (!a[x])
            {
                turnon(x);
                a[x] = true;
                --tot;
            }
            else
            {
                turnoff(x);
                a[x] = false;
                ++tot;
            }
        }
        else
        {
            if (tot == 0)
                printf("-1\n");
            else if (tot == 1)
                printf("0\n");
            else
                printf("%d\n", all.top());
        }
    }
    return 0;
}