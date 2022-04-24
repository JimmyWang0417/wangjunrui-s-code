#include <cstdio>
#include <queue>
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
constexpr int N = 5e5 + 5, M = 2e6 + 5;
int n, s, m;
struct Edge
{
    int next, to, dis;
} edge[M];
int head[N], num_edge;
int in[N];
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
    ++in[to];
}
bool vis[N];
int dis[N];
int where[N];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        where[l] = rt;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    add_edge(rt, lc, 0);
    add_edge(rt, rc, 0);
}
inline void update(int rt, int l, int r, int x, int y, int u)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return add_edge(u, rt, -1);
    int mid = (l + r) >> 1;
    update(lc, l, mid, x, y, u);
    update(rc, mid + 1, r, x, y, u);
}
signed main()
{
    read(n, s, m);
    build(1, 1, n);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        ckmax(cnt, where[i]);
    for (int i = 1; i <= s; ++i)
    {
        int x, y;
        read(x, y);
        dis[where[x]] = y;
        vis[where[x]] = true;
    }
    for (int i = 1; i <= m; ++i)
    {
        int l, r, k;
        read(l, r, k);
        ++cnt;
        int las = l;
        while (k--)
        {
            int x;
            read(x);
            update(1, 1, n, las, x - 1, cnt);
            add_edge(where[x], cnt, 0);
            las = x + 1;
        }
        update(1, 1, n, las, r, cnt);
    }
    queue<int> q;
    for (int i = 1; i <= cnt; ++i)
    {
        if (!dis[i])
            dis[i] = 1e9;
        if (!in[i])
            q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
            {
                if (vis[v])
                {
                    printf("NIE\n");
                    return 0;
                }
                dis[v] = dis[u] + edge[i].dis;
            }
            if (!--in[v])
                q.push(v);
        }
    }
    for (int i = 1; i <= cnt; ++i)
        if (dis[i] < 1 || in[i])
        {
            printf("NIE\n");
            return 0;
        }
    printf("TAK\n");
    for (int i = 1; i <= n; ++i)
        printf("%d ", dis[where[i]]);
    putchar('\n');
    return 0;
}