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
using namespace std;
const int N = 2e5 + 5;
struct SAM
{
    map<int, int> ch;
    int len, fa, id, size;
} point[N];
int tot = 1, las = 1;
inline int insert(int c, int id)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[np].fa = point[q].fa = nq;
            point[nq].len = point[p].len + 1;
            for (; p && q == point[p].ch[c]; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
    for (p = np; p && point[p].id != id; p = point[p].fa)
    {
        ++point[p].size;
        point[p].id = id;
    }
    return np;
}
int n, m;
vector<int> g[N];
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
int dfn[N], low[N], dfstime, dep[N];
int fa[N][20];
inline void dfs(int u)
{
    for (int i = 0; i < 18; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    dfn[u] = ++dfstime;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        fa[v][0] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
    }
    low[u] = dfstime;
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 18; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 18; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
struct Tree_array
{
    int sum[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= dfstime; i += lowbit(i))
            sum[i] += val;
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
            res += sum[i];
        return res;
    }
} tree;
int answer[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int c, x;
        read(c);
        while (c--)
        {
            read(x);
            g[i].push_back(insert(x, i));
        }
        las = 1;
        read(c);
        while (c--)
        {
            read(x);
            g[i].push_back(insert(x, i));
        }
        las = 1;
    }
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dep[1] = 1;
    dfs(1);
    for (int now = 1; now <= n; ++now)
    {
        sort(g[now].begin(), g[now].end(), [](const int &x, const int &y)
             { return dfn[x] < dfn[y]; });
        ++answer[g[now][0]];
        for (int i = 1; i < (int)g[now].size(); ++i)
        {
            ++answer[g[now][i]];
            --answer[getlca(g[now][i - 1], g[now][i])];
        }
    }
    for (int i = tot; i >= 2; --i)
        answer[point[i].fa] += answer[i];
    for (int i = 1; i <= m; ++i)
    {
        int c, x, u = 1;
        read(c);
        while (c--)
        {
            read(x);
            u = point[u].ch[x];
        }
        if (!u)
        {
            puts("0");
            continue;
        }
        printf("%d\n", point[u].size);
        tree.update(dfn[u], low[u], 1);
    }
    for (int now = 1; now <= n; ++now)
    {
        sort(g[now].begin(), g[now].end(), [](const int &x, const int &y)
             { return dfn[x] < dfn[y]; });
        int res = tree.query(dfn[g[now][0]]);
        for (int i = 1; i < (int)g[now].size(); ++i)
            res += tree.query(dfn[g[now][i]]) - tree.query(dfn[getlca(g[now][i - 1], g[now][i])]);
        printf("%d ", res);
    }
    putchar('\n');
    return 0;
}