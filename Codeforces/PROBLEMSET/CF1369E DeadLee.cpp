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
const int N = 4e5 + 5;
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int n, m, a[N];
bool vis[N];
int answer[N], tot;
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
        --a[u], --a[v];
    }
    queue<int, list<int>> q;
    for (int i = 1; i <= n; ++i)
        if (a[i] >= 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            if (vis[v])
                continue;
            answer[++tot] = i >> 1;
            ++a[v];
            if (a[v] == 0)
                q.push(v);
        }
    }
    if (tot < m)
    {
        printf("DEAD\n");
        return 0;
    }
    printf("ALIVE\n");
    for (int i = tot; i >= 1; --i)
        printf("%d ", answer[i]);
    putchar('\n');
    return 0;
}