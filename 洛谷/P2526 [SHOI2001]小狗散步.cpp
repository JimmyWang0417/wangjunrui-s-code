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
const int N = 105;
struct Edge
{
    int next, to;
} edge[N * N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int n, m;
struct Point
{
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    inline Point operator-(const Point &rhs) const
    {
        return Point(x - rhs.x, y - rhs.y);
    }
    inline double norm()
    {
        return sqrt(x * x + y * y);
    }
    inline void init()
    {
        read(x, y);
    }
} a[N], b[N];
bitset<N> vis;
int belong[N];
int id[N][N];
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
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        a[i].init();
    for (int i = 1; i <= m; ++i)
        b[i].init();
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            if ((a[i + 1] - a[i]).norm() * 2 >= (b[j] - a[i]).norm() + (b[j] - a[i + 1]).norm())
                add_edge(j, i);
    }
    int res = 0;
    for (int i = 1; i <= m; ++i)
    {
        res += find(i);
        vis.reset();
    }
    printf("%d\n", n + res);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d %d ", a[i].x, a[i].y);
        if (belong[i])
            printf("%d %d ", b[belong[i]].x, b[belong[i]].y);
    }
    return 0;
}