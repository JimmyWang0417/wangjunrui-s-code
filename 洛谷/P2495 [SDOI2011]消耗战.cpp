#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T &x)
{
    x = 0;
    char s = (char)getchar();
    bool flag = false;
    while (s < '0' || s > '9')
    {
        if (s == '-')
            flag = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + (s ^ '0');
        s = (char)getchar();
    }
    if (flag)
        x = ~x + 1;
    return;
}
const int N = 250000 + 5;
struct Edge
{
    int next, to, dis;
} edge[N << 1];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int dfn[N], top[N], fa[N], size[N], son[N], dfstime, dep[N];
ll mindis[N];
inline void dfs1(int u, int fa_)
{
    fa[u] = fa_;
    size[u] = 1;
    for (re int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == fa_)
            continue;
        mindis[v] = min(mindis[u], (ll)edge[i].dis);
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
inline void dfs2(int u, int topf)
{
    top[u] = topf;
    dfn[u] = ++dfstime;
    if (!son[u])
        return;
    dfs2(son[u], topf);
    for (re int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (top[v])
            continue;
        dfs2(v, v);
    }
}
inline int LCA(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}

vector<int> aux[N];
inline void add(int x, int y)
{
    aux[x].push_back(y);
    return;
}
int st[N], tp;
inline void insert(int u)
{
    if (tp == 1)
    {
        st[++tp] = u;
        return;
    }
    int lca = LCA(st[tp], u);
    if (lca == st[tp])
        return;
    while (tp > 1 && dfn[lca] <= dfn[st[tp - 1]])
    {
        add(st[tp - 1], st[tp]);
        --tp;
    }
    if (lca != st[tp])
    {
        add(lca, st[tp]);
        st[tp] = lca;
    }
    st[++tp] = u;
}
bool tag[N];
inline ll dp(int u)
{
    //	printf(" %d:",u);
    if (aux[u].size() == 0)
        return mindis[u];
    ll tmp = 0ll;
    for (re int i = 0; i < aux[u].size(); ++i)
        tmp += dp(aux[u][i]);
    aux[u].clear();
    return min(tmp, mindis[u]);
}
int n, m, q, a[N];
inline bool cmp(const int &rhsx, const int &rhsy)
{
    return dfn[rhsx] < dfn[rhsy];
}
inline void work()
{
    read(m);
    for (re int i = 1; i <= m; ++i)
    {
        read(a[i]);
        tag[a[i]] = true;
    }
    sort(a + 1, a + 1 + m, cmp);
    st[tp = 1] = 1;
    for (re int i = 1; i <= m; ++i)
        insert(a[i]);
    while (tp > 1)
    {
        add(st[tp - 1], st[tp]);
        --tp;
    }
    //	for(re int i=1; i<=n; ++i)
    //	{
    //		printf("\n%d:",i);
    //		for(re int j=0; j<aux[i].size(); ++j)
    //			printf(" %d ",aux[i][j]);
    //	}

    printf("%lld\n", dp(1));
    //	putchar('\n');
}
const ll INF = 1e18;
int main()
{
    read(n);
    for (re int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u), read(v), read(w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    mindis[1] = INF;
    dfs1(1, 0);
    dfs2(1, 1);
    //	for(re int i=1; i<=n; ++i)
    //		printf("%d %d %d %lld %d\n",dfn[i],top[i],size[i],mindis[i],son[i]);
    read(q);
    while (q--)
        work();
}
