#include <bits/stdc++.h>
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
const int N = 1e5 + 5, M = 1e6 + 5;
const int INF = 0x3f3f3f3f;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
struct Edge
{
    int next, to, flow, cap;
} edge[M];
int head[N], num_edge = 1;
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
int dis[N];
bool exist[N];
int cur[N];
int P, Q, R, D;
#define s 0
#define t (P * Q * R + 1)
inline bool bfs()
{
    memset(dis, 0, sizeof(dis));
    memcpy(cur, head, sizeof(head));
    queue<int> q;
    dis[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (edge[i].cap > edge[i].flow && !dis[v])
            {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t];
}
inline int dinic(int u, int flow)
{
    if (u == t)
        return flow;
    int res = 0;
    for (int &i = cur[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (dis[v] == dis[u] + 1 && edge[i].cap > edge[i].flow)
        {
            int f = dinic(v, min(flow, edge[i].cap - edge[i].flow));
            if (f)
            {
                res += f;
                flow -= f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
                if (!flow)
                    break;
            }
        }
    }
    return res;
}
inline int calc(int i, int j, int k)
{
    return ((i - 1) * Q + j - 1) * R + k;
}
signed main()
{
    read(P, Q, R, D);
    for (int k = 1; k <= R; ++k)
        for (int i = 1; i <= P; ++i)
            for (int j = 1; j <= Q; ++j)
            {
                int val;
                read(val);
                if (k == 1)
                    add_edge(s, calc(i, j, k), val);
                else
                    add_edge(calc(i, j, k - 1), calc(i, j, k), val);
            }
    for (int i = 1; i <= P; ++i)
        for (int j = 1; j <= Q; ++j)
        {
            for (int k = D + 1; k <= R; ++k)
            {
                for (int d = 0; d < 4; ++d)
                {
                    int x = i + dx[d], y = j + dy[d];
                    if (1 <= x && x <= P && 1 <= y && y <= Q)
                        add_edge(calc(i, j, k), calc(x, y, k - D), INF);
                }
            }
            add_edge(calc(i, j, R), t, INF);
        }
    int ans = 0;
    while (bfs())
        ans += dinic(s, INF);
    printf("%d\n", ans);
    return 0;
}
