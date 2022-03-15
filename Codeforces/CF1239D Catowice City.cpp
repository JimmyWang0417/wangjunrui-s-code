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
const int N = 1e6 + 5;
int n, m;
struct Edge
{
    int next, to;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int dfn[N], low[N], dfstime;
int st[N], top;
int belong[N], color, size[N];
inline void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (!dfn[v])
        {
            tarjan(v);
            ckmin(low[u], low[v]);
        }
        else if (!belong[v])
            ckmin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        belong[u] = ++color;
        ++size[color];
        while (st[top] != u)
        {
            belong[st[top--]] = color;
            ++size[color];
        }
        --top;
    }
}
inline void work()
{
    fill(belong + 1, belong + 1 + n, color = 0);
    fill(head + 1, head + 1 + n, num_edge = 0);
    fill(size + 1, size + 1 + n, 0);
    fill(dfn + 1, dfn + 1 + n, dfstime = 0);
    top = 0;
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        if (u == v)
            continue;
        add_edge(u, v);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    if (color == 1)
    {
        printf("No\n");
        return;
    }
    printf("Yes\n%d %d\n", size[1], n - size[1]);
    for (int i = 1; i <= n; ++i)
        if (belong[i] == 1)
            printf("%d ", i);
    putchar('\n');
    for (int i = 1; i <= n; ++i)
        if (belong[i] != 1)
            printf("%d ", i);
    putchar('\n');
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}