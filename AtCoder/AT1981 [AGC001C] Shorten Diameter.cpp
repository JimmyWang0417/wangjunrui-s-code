#include <bits/stdc++.h>
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
constexpr int N = 2005;
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
int answer = 0;
inline void dfs(int u, int _fa, int len)
{
    if (len < 0)
        ++answer;
    --len;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u, len);
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    int res = INT_MAX;
    if (m & 1)
    {
        m >>= 1;
        for (int u = 1; u <= n; ++u)
            for (int i = head[u]; i; i = edge[i].next)
                if (i & 1)
                {
                    int &v = edge[i].to;
                    dfs(v, u, m);
                    dfs(u, v, m);
                    ckmin(res, answer);
                    answer = 0;
                }
    }
    else
    {
        m >>= 1;
        for (int i = 1; i <= n; ++i)
        {
            dfs(i, 0, m);
            ckmin(res, answer);
            answer = 0;
        }
    }
    printf("%d\n", res);
    return 0;
}