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
constexpr int N = 505, M = 1e6 + 5;
int n, m1, m2;
struct Edge
{
    int next, to, flow, cap;
} edge[M];
int head[N], num_edge;
inline void add_edge(int from, int to, int cap, bool flag = true)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].flow = 0;
    edge[num_edge].cap = cap;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, false);
}
int dis[N], cur[N];
bool exist[N];
int S, T;
inline bool bfs()
{
    memset(exist, 0, sizeof(exist));
    memset(dis, 0, sizeof(dis));
    memcpy(cur, head, sizeof(cur));
    queue<int> q;
    q.push(S);
    dis[S] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (!dis[v] && edge[i].cap > edge[i].flow)
            {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[T];
}
inline int dinic(int u, int flow)
{
    if (u == T)
        return flow;
    int res = 0;
    exist[u] = true;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (!exist[v] && edge[i].cap > edge[i].flow && dis[v] == dis[u] + 1)
        {
            int f = dinic(v, min(flow, edge[i].cap - edge[i].flow));
            if (f)
            {
                res += f;
                flow -= f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
                if (!flow)
                {
                    exist[u] = false;
                    break;
                }
            }
        }
    }
    return res;
}
ll answer;
int a[N];
vector<int> g[N];
bool mp[N][N];
int q[N], q1[N], q2[N];
int p[N], tot;
inline int calc(int x, int y)
{
    return (int)(2 * (upper_bound(g[x].begin(), g[x].end(), y) - g[x].begin()) - g[x].size());
}
inline void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; ++i)
        {
            for (auto u : g[q[i]])
                answer += abs(p[u] - p[l]);
        }
        return;
    }
    int mid = (l + r) >> 1;
    memset(head, 0, sizeof(head));
    num_edge = 1;
    for (int i = ql; i <= qr; ++i)
    {
        int val = calc(q[i], mid);
        if (val <= 0)
            add_edge(S, i, -val);
        else
            add_edge(i, T, val);
    }
    for (int i = ql; i <= qr; ++i)
    {
        for (int j = ql; j <= qr; ++j)
            if (mp[q[i]][q[j]])
                add_edge(i, j, INT_MAX);
    }
    int cnt1 = 0, cnt2 = 0;
    while (bfs())
        dinic(S, INT_MAX);
    for (int i = ql; i <= qr; ++i)
        if (!dis[i])
            q1[++cnt1] = q[i];
        else
            q2[++cnt2] = q[i];
    for (int i = 1; i <= cnt1; ++i)
        q[ql + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i)
        q[qr - cnt2 + i] = q2[i];
    solve(l, mid, ql, ql + cnt1 - 1);
    solve(mid + 1, r, qr - cnt2 + 1, qr);
}
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
signed main()
{
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    read(n, m1, m2);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[++tot] = a[i];
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    for (int i = 1; i <= n; ++i)
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
    for (int i = 1; i <= m1; ++i)
    {
        int x, y;
        read(x, y);
        x = find(x), y = find(y);
        if (x == y)
            continue;
        fa[x] = y;
    }
    for (int i = 1; i <= m2; ++i)
    {
        int x, y;
        read(x, y);
        mp[find(x)][find(y)] = true;
    }
    for (int i = 1; i <= n; ++i)
        g[find(i)].push_back(a[i]);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (i == find(i))
        {
            sort(g[i].begin(), g[i].end());
            q[++cnt] = i;
        }
    S = 0, T = cnt + 1;
    solve(1, tot, 1, cnt);
    printf("%lld\n", answer);
    return 0;
}
