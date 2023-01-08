#include <cstdio>
#include <cstring>
#include <queue>
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
constexpr int N = 2005, M = 1e4 + 5;
int n, m;
struct Edge
{
    int next, to, flow, cap, cost;
} edge[M * 3];
int head[M], num_edge = 1;
inline void add_edge(int from, int to, int cap, int cost, bool flag = true)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].flow = 0;
    edge[num_edge].cap = cap;
    edge[num_edge].cost = cost;
    head[from] = num_edge;
    if (flag)
        add_edge(to, from, 0, -cost, false);
}
int dis[M], cur[M];
bool exist[M];
int S, T;
inline bool spfa()
{
    memcpy(cur, head, sizeof(int) * (T + 1));
    memset(dis, 0x3f, sizeof(int) * (T + 1));
    memset(exist, 0, sizeof(bool) * (T + 1));
    dis[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].cost && edge[i].cap > edge[i].flow)
            {
                dis[v] = dis[u] + edge[i].cost;
                if (!exist[v])
                {
                    q.push(v);
                    exist[v] = false;
                }
            }
        }
    }
    return dis[T] < 0x3f3f3f3f;
}
inline int dinic(int u, int flow)
{
    if (u == T)
        return flow;
    exist[u] = true;
    int res = 0;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (!exist[v] && dis[v] == dis[u] + edge[i].cost && edge[i].cap > edge[i].flow)
        {
            int f = dinic(v, std::min(flow, edge[i].cap - edge[i].flow));
            if (f)
            {
                res += f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
                flow -= f;
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
vector<int> g[16];
constexpr int up = 0, right = 1, down = 2, left = 3;
int id[N][N][5], cnt;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 4; ++j)
            if ((i >> j) & 1)
                g[i].push_back(j);
    }
    read(n, m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            id[i][j][0] = ++cnt;
            id[i][j][1] = ++cnt;
            id[i][j][2] = ++cnt;
            id[i][j][3] = ++cnt;
            id[i][j][4] = ++cnt;
            // for (int k = 0; k <= 4; ++k)
            //     printf("id[%d][%d][%d]=%d\n", i, j, k, id[i][j][k]);
        }
    int sum1 = 0, sum2 = 0;
    S = 0, T = n * m * 5 + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int x;
            read(x);
            if (g[x].size() == 0)
                continue;
            if ((i + j) & 1)
            {
                sum1 += (int)g[x].size();
                add_edge(S, id[i][j][4], (int)g[x].size(), 0);
                if (i < n)
                    add_edge(id[i][j][2], id[i + 1][j][0], 1, 0);
                if (i > 1)
                    add_edge(id[i][j][0], id[i - 1][j][2], 1, 0);
                if (j < m)
                    add_edge(id[i][j][1], id[i][j + 1][3], 1, 0);
                if (j > 1)
                    add_edge(id[i][j][3], id[i][j - 1][1], 1, 0);
                if (g[x].size() == 1)
                {
                    int y = g[x][0];
                    add_edge(id[i][j][4], id[i][j][y], 1, 0);
                    add_edge(id[i][j][4], id[i][j][(y + 1) % 4], 1, 1);
                    add_edge(id[i][j][4], id[i][j][(y + 3) % 4], 1, 1);
                    add_edge(id[i][j][4], id[i][j][(y + 2) % 4], 1, 2);
                }
                else if (g[x].size() == 2)
                {
                    int y = g[x][0], z = g[x][1];
                    if ((y + 2) % 4 == z)
                    {
                        add_edge(id[i][j][4], id[i][j][y], 1, 0);
                        add_edge(id[i][j][4], id[i][j][z], 1, 0);
                    }
                    else
                    {
                        add_edge(id[i][j][4], id[i][j][y], 1, 0);
                        add_edge(id[i][j][4], id[i][j][z], 1, 0);
                        add_edge(id[i][j][y], id[i][j][(y + 2) % 4], 1, 1);
                        add_edge(id[i][j][z], id[i][j][(z + 2) % 4], 1, 1);
                    }
                }
                else if (g[x].size() == 3)
                {
                    int y = g[15 ^ x][0];
                    for (auto u : g[x])
                        add_edge(id[i][j][4], id[i][j][u], 1, 0);
                    add_edge(id[i][j][(y + 1) % 4], id[i][j][y], 1, 1);
                    add_edge(id[i][j][(y + 3) % 4], id[i][j][y], 1, 1);
                    add_edge(id[i][j][(y + 2) % 4], id[i][j][y], 1, 2);
                }
                else
                {
                    for (int k = 0; k < 4; ++k)
                        add_edge(id[i][j][4], id[i][j][k], 1, 0);
                }
            }
            else
            {
                sum2 += (int)g[x].size();
                add_edge(id[i][j][4], T, (int)g[x].size(), 0);
                if (g[x].size() == 1)
                {
                    int y = g[x][0];
                    add_edge(id[i][j][y], id[i][j][4], 1, 0);
                    add_edge(id[i][j][(y + 1) % 4], id[i][j][4], 1, 1);
                    add_edge(id[i][j][(y + 3) % 4], id[i][j][4], 1, 1);
                    add_edge(id[i][j][(y + 2) % 4], id[i][j][4], 1, 2);
                }
                else if (g[x].size() == 2)
                {
                    int y = g[x][0], z = g[x][1];
                    if ((y + 2) % 4 == z)
                    {
                        add_edge(id[i][j][y], id[i][j][4], 1, 0);
                        add_edge(id[i][j][z], id[i][j][4], 1, 0);
                    }
                    else
                    {
                        add_edge(id[i][j][y], id[i][j][4], 1, 0);
                        add_edge(id[i][j][z], id[i][j][4], 1, 0);
                        add_edge(id[i][j][(y + 2) % 4], id[i][j][y], 1, 1);
                        add_edge(id[i][j][(z + 2) % 4], id[i][j][z], 1, 1);
                    }
                }
                else if (g[x].size() == 3)
                {
                    int y = g[15 ^ x][0];
                    for (auto u : g[x])
                        add_edge(id[i][j][u], id[i][j][4], 1, 0);
                    add_edge(id[i][j][y], id[i][j][(y + 1) % 4], 1, 1);
                    add_edge(id[i][j][y], id[i][j][(y + 3) % 4], 1, 1);
                    add_edge(id[i][j][y], id[i][j][(y + 2) % 4], 1, 2);
                }
                else
                {
                    for (int k = 0; k < 4; ++k)
                        add_edge(id[i][j][k], id[i][j][4], 1, 0);
                }
            }
        }
    int ans = 0, flow = 0;
    while (spfa())
    {
        int f = dinic(S, 0x3f3f3f3f);
        flow += f;
        ans += f * dis[T];
    }
    // printf("%lld %d\n", ans, flow);
    if (flow == sum1 && flow == sum2)
        printf("%d\n", ans);
    else
        printf("-1\n");
    return 0;
}
