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
constexpr int N = 1005;
constexpr int limit = 1e6;
int n, m;
int a[N][N], b[N][N];
struct Edge
{
    int next, to, dis;
} edge[N * N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
int S;
ll dis[N];
int deg[N];
bool exist[N];
inline void work()
{
    memset(head, num_edge = 0, sizeof(head));
    memset(a, 0, sizeof(a));
    read(n, m);
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            read(b[i][j]);
    for (int i = n - 1; i >= 1; --i)
        for (int j = m - 1; j >= 1; --j)
            a[i][j] = b[i][j] - a[i + 1][j] - a[i][j + 1] - a[i + 1][j + 1];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if ((i + j) & 1)
            {
                add_edge(i, j + n, a[i][j]);
                add_edge(j + n, i, limit - a[i][j]);
            }
            else
            {
                add_edge(j + n, i, a[i][j]);
                add_edge(i, j + n, limit - a[i][j]);
            }
        }
    queue<int> q;
    for (int i = 1; i <= n + m; ++i)
    {
        dis[i] = deg[i] = 0;
        exist[i] = true;
        q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].dis)
            {
                dis[v] = dis[u] + edge[i].dis;
                if (++deg[v] > n + m)
                {
                    printf("NO\n");
                    return;
                }
                if (!exist[v])
                {
                    q.push(v);
                    exist[v] = true;
                }
            }
        }
    }
    printf("YES\n");
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            printf("%lld ", a[i][j] + ((i + j) & 1 ? dis[i] - dis[j + n] : dis[j + n] - dis[i]));
        putchar('\n');
    }
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}