#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
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
constexpr int N = 105;
int n, m;
char str[N][N];
struct Edge
{
    int next, to;
} edge[N * N * 4];
int head[N * N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
bitset<N * N> vis, exist;
int belong[N * N];
inline int calc(int x, int y)
{
    return (x - 1) * m + y;
}
inline bool find(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        vis.set(v);
        if (!belong[v] || find(belong[v]))
        {
            belong[v] = u;
            return true;
        }
    }
    return false;
}
inline bool check(int u)
{
    if (!belong[u])
        return false;
    vis.set(u);
    u = belong[u];
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (vis[v])
            continue;
        if (!check(v))
            return false;
    }
    return true;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif
    while (read(n, m), n && m)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%s", str[i] + 1);
        memset(head, num_edge = 0, sizeof(head));
        memset(belong, 0, sizeof(belong));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (str[i][j] == '.')
                {
                    if (i < n && str[i + 1][j] == '.')
                        add_edge(calc(i, j), calc(i + 1, j));
                    if (i > 1 && str[i - 1][j] == '.')
                        add_edge(calc(i, j), calc(i - 1, j));
                    if (j < m && str[i][j + 1] == '.')
                        add_edge(calc(i, j), calc(i, j + 1));
                    if (j > 1 && str[i][j - 1] == '.')
                        add_edge(calc(i, j), calc(i, j - 1));
                }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (str[i][j] == '.')
                {
                    exist[calc(i, j)] = find(calc(i, j));
                    vis.reset();
                }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
                if (str[i][j] == '.')
                {
                    exist[calc(i, j)] = check(calc(i, j));
                    if (exist[calc(i, j)])
                        putchar('A');
                    else
                        putchar('B');
                    vis.reset();
                }
                else
                    putchar('X');
            putchar('\n');
        }
    }
    return 0;
}
