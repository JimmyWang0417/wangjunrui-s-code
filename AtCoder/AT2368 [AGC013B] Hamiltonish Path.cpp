#include <cstdio>
#include <list>
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
constexpr int N = 1e5 + 5;
int n, m;
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
list<int> g[N], answer;
bool vis[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int rootl = 0, rootr = 0;
    for (int u = 1; u <= n; ++u)
    {
        while (!g[u].empty())
        {
            if (vis[g[u].front()])
            {
                g[u].pop_front();
                continue;
            }
            vis[rootl = u] = vis[rootr = g[u].front()] = true;
            g[u].pop_front();
            goto solve;
        }
    }
solve:
    answer.push_front(rootl);
    answer.push_back(rootr);
    while (!g[rootl].empty())
    {
        while (!g[rootl].empty())
        {
            if (vis[g[rootl].front()])
            {
                g[rootl].pop_front();
                continue;
            }
            answer.push_front(rootl = g[rootl].front());
            vis[rootl] = true;
            break;
        }
    }
    while (!g[rootr].empty())
    {
        while (!g[rootr].empty())
        {
            if (vis[g[rootr].back()])
            {
                g[rootr].pop_back();
                continue;
            }
            answer.push_back(rootr = g[rootr].back());
            vis[rootr] = true;
            break;
        }
    }
    printf("%lu\n", answer.size());
    for (auto u : answer)
        printf("%d ", u);
    putchar('\n');
    return 0;
}
