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
int p[N], tot;
struct Query
{
    int opt, a, b, lca, v;
} q[N], q1[N], q2[N];
int n, m;
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int dfn[N], low[N], dfstime;
int Log[N], dep[N], fa[N][20];
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    fa[u][0] = _fa;
    for (int i = 0; i < Log[dep[u]]; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    dfn[u] = ++dfstime;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
    low[u] = dfstime;
}
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = Log[dep[u]]; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
struct Tree_array
{
    int c[N];
    inline void update(int pos, int val)
    {
        if (!pos)
            return;
        for (int i = pos; i <= dfstime; i += lowbit(i))
            c[i] += val;
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
    inline void clear(int pos)
    {
        if (!pos)
            return;
        for (int i = pos; i <= dfstime && c[i]; i += lowbit(i))
            c[i] = 0;
    }
    inline int query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
} tree;
int answer[N];
inline void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; ++i)
            if (q[i].opt == 2)
                answer[q[i].b] = p[l];
        return;
    }
    int mid = (l + r + 1) >> 1;
    int cnt1 = 0, cnt2 = 0;
    int now=0;
    for (int i = ql; i <= qr; ++i)
    {
        if (q[i].opt == 0)
        {
            if (q[i].v < p[mid])
                q1[++cnt1] = q[i];
            else
            {
                tree.update(dfn[q[i].a], 1);
                tree.update(dfn[q[i].b], 1);
                tree.update(dfn[q[i].lca], -1);
                tree.update(dfn[fa[q[i].lca][0]], -1);
                ++now;
                q2[++cnt2] = q[i];
            }
        }
        else if (q[i].opt == 1)
        {
            if (q[i].v < p[mid])
                q1[++cnt1] = q[i];
            else
            {
                tree.update(dfn[q[i].a], -1);
                tree.update(dfn[q[i].b], -1);
                tree.update(dfn[q[i].lca], 1);
                tree.update(dfn[fa[q[i].lca][0]], 1);
                --now;
                q2[++cnt2] = q[i];
            }
        }
        else
        {
            if (now-(tree.query(dfn[q[i].a],low[q[i].a])))
                q2[++cnt2] = q[i];
            else
                q1[++cnt1] = q[i];
        }
    }
    for (int i = 1; i <= cnt1; ++i)
        q[ql + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i)
    {
        q[qr - cnt2 + i] = q2[i];
        if (q2[i].opt == 0)
        {
            tree.clear(dfn[q2[i].a]);
            tree.clear(dfn[q2[i].b]);
            tree.clear(dfn[q2[i].lca]);
            tree.clear(dfn[fa[q2[i].lca][0]]);
        }
    }
    solve(l, mid - 1, ql, ql + cnt1 - 1);
    solve(mid, r, qr - cnt2 + 1, qr);
}
signed main()
{
    read(n, m);
	Log[0]=-1;
	for(int i=1;i<=n;++i)
	Log[i]=Log[i>>1]+1;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    int ctime = 0;
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].opt);
        if (q[i].opt == 0)
        {
            read(q[i].a, q[i].b, q[i].v);
            q[i].lca = getlca(q[i].a, q[i].b);
            p[++tot] = q[i].v;
        }
        else if (q[i].opt == 1)
        {
            int id;
            read(id);
            q[i].a=q[id].a,q[i].b=q[id].b,q[i].lca=q[id].lca,q[i].v=q[id].v;
        }
        else
        {
            read(q[i].a);
            q[i].b = ++ctime;
        }
    }
    p[0] = -1;
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    solve(0, tot, 1, m);
    for (int i = 1; i <= ctime; ++i)
        printf("%d\n", answer[i]);
    return 0;
}