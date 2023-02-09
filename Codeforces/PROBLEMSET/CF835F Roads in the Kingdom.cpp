#include <bits/stdc++.h>
#define int ll
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 4e5 + 5;
int n;
struct Edge
{
    int next, to, dis;
} edge[N * 2];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int dfn[N], dfstime;
int lasedge[N], fa[N];
pair<int, int> a[N];
int cnt = 0;
bool exist[N];
inline void dfs(int u, int _fa)
{
    dfn[u] = ++dfstime;
    fa[u] = _fa;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa)
            continue;
        if (!dfn[v])
        {
            dfs(v, u);
            lasedge[v] = i;
        }
        else
        {
            if (dfn[u] < dfn[v])
            {
                int x = v;
                while (x != u)
                {
                    a[++cnt] = make_pair(x, edge[lasedge[x]].dis);
                    exist[x] = true;
                    x = fa[x];
                }
                exist[u] = true;
                a[++cnt] = make_pair(u, edge[i].dis);
            }
        }
    }
}
int root;
ll dis[N], maxdis[N];
inline void findroot(int u, int _fa)
{
    if (dis[root] < dis[u])
        root = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == _fa || exist[v])
            continue;
        dis[v] = dis[u] + edge[i].dis;
        findroot(v, u);
    }
}
inline ll solve(int u)
{
    exist[u] = false;
    root = u;
    dis[u] = 0;
    findroot(u, 0);
    dis[root] = 0;
    findroot(root, 0);
    exist[u] = true;
    return dis[root];
}
inline void work(int u)
{
    root = u;
    dis[u] = 0;
    findroot(u, 0);
    maxdis[u] = dis[root];
}
int pre[N], suf[N];
int L[N], R[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dfs(1, 0);
    a[0] = a[cnt];
    ll all = 0;
    for (int i = 1; i <= cnt; ++i)
        all = max(all, solve(a[i].first));
    memset(dis, 0, sizeof(dis));
    for (int i = 1; i <= cnt; ++i)
        work(a[i].first);
    //	putchar('\n');
    //	for(int i=1; i<=cnt; ++i)
    //		printf("%lld ",a[i].first);
    //	putchar('\n');
    for (int i = 1; i <= cnt; ++i)
        dis[i] = dis[i - 1] + a[i - 1].second;
    //	for(int i=1; i<=cnt; ++i)
    //		printf("%lld ",dis[i]);
    //	putchar('\n');
    //	for(int i=1; i<=cnt; ++i)
    //		printf(" %d",a[i].first);
    //	putchar('\n');
    ll ans = 0, now = pre[0] = -1e18;
    L[0] = -1e18;
    for (int i = 1; i <= cnt; ++i)
    {
        L[i] = max(L[i - 1], now + maxdis[a[i].first] + dis[i]);
        pre[i] = max(pre[i - 1], maxdis[a[i].first] + dis[i]);
        now = max(now, maxdis[a[i].first] - dis[i]);
    }
    ans = L[cnt];

    R[cnt + 1] = -1e18;
    suf[cnt + 1] = now = -1e18;
    for (int i = cnt; i >= 1; --i)
    {
        R[i] = max(R[i + 1], now + maxdis[a[i].first] + (dis[cnt] - dis[i]));
        suf[i] = max(suf[i + 1], maxdis[a[i].first] + (dis[cnt] - dis[i]));
        now = max(now, maxdis[a[i].first] - (dis[cnt] - dis[i]));
    }
    for (int i = 1; i < cnt; ++i)
        ans = min(ans, max(max(L[i], R[i + 1]), pre[i] + suf[i + 1]));
    printf("%lld\n", max(ans, all));
    return 0;
}
