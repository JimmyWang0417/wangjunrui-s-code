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
const int N = 1005;
int n, m, in[N * 2];
struct Edge
{
    int next, to;
} edge[N * N];
int head[N * 2], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
    ++in[to];
}
char str[N][N];
int fa[N * 2];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline void unionn(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    fa[x] = y;
}
int dis[N * 2];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= m; ++j)
            if (str[i][j] == '=')
                unionn(i, j + n);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            if (str[i][j] == '<')
                add_edge(find(i), find(j + n));
            else if (str[i][j] == '>')
                add_edge(find(j + n), find(i));
    }
    int color = 0;
    queue<int> q;
    for (int i = 1; i <= n + m; ++i)
        if (!fa[i])
        {
            ++color;
            if (!in[i])
                q.push(i);
        }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ++dis[u];
        --color;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            dis[v] = max(dis[v], dis[u]);
            if (!--in[v])
                q.push(v);
        }
    }
    if (color)
        printf("No\n");
    else
    {
        printf("Yes\n");
        for (int i = 1; i <= n; ++i)
            printf("%d ", dis[find(i)]);
        putchar('\n');
        for (int i = 1; i <= m; ++i)
            printf("%d ", dis[find(i + n)]);
        putchar('\n');
    }
    return 0;
}
