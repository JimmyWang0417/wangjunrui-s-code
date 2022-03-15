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
const int N = 4e4 + 5, NUM = 45;
int n, m, a[N];
int p[N], tot;
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
const int block = 1000;
int belong[N], capital[NUM], color;
int st[N], top;
int dep[N];
int fa[N];
inline void dfs(int u, int _fa)
{
    fa[u] = _fa;
    dep[u] = dep[_fa] + 1;
    int lastop = top;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        if (top - block >= lastop)
        {
            ++color;
            capital[color] = u;
            while (top > lastop)
                belong[st[top--]] = color;
        }
    }
    st[++top] = u;
}
bitset<N> answer[NUM][NUM];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[i] = a[i];
    }
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; ++i)
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    if (top)
    {
        ++color;
        capital[color] = 1;
        while (top)
            belong[st[top--]] = color;
    }
    for (int i = 1; i <= color; ++i)
        for (int j = i + 1; j <= color; ++j)
        {
            int u = capital[i], v = capital[j];
            if (dep[u] < dep[v])
                swap(u, v);
            while (dep[u] > dep[v])
            {
                answer[i][j].flip(a[u]);
                u = fa[u];
            }
            if (u == v)
            {
                answer[i][j].flip(a[u]);
                answer[j][i] = answer[i][j];
                continue;
            }
            while (u != v)
            {
                answer[i][j].flip(a[u]), answer[i][j].flip(a[v]);
                u = fa[u], v = fa[v];
            }
            answer[i][j].flip(a[u]);
            answer[j][i] = answer[i][j];
        }
    return 0;
}
