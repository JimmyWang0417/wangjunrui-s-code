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
const int N = 2e5 + 5;
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
int n;
unordered_map<ll, int> mp;
int dep[N], root;
inline void dfs(int u, int _fa)
{
    dep[u] = dep[_fa] + 1;
    if (dep[u] > dep[root])
        root = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
    }
}
signed main()
{
    read(n);
    for (int i = 1; i < n - 1; ++i)
    {
        int x, y, z;
        read(x, y, z);
        if (x > y)
            swap(x, y);
        if (x > z)
            swap(x, z);
        if (y > z)
            swap(y, z);
        int res = mp[(ll)x * n + y];
        if (!res)
            mp[(ll)x * n + y] = i;
        else
        {
            add_edge(i, res);
            add_edge(res, i);
        }
        res = mp[(ll)x * n + z];
        if (!res)
            mp[(ll)x * n + z] = i;
        else
        {
            add_edge(i, res);
            add_edge(res, i);
        }
        res = mp[(ll)y * n + z];
        if (!res)
            mp[(ll)y * n + z] = i;
        else
        {
            add_edge(i, res);
            add_edge(res, i);
        }
    }
    dfs(1, 0);
    dfs(root, 0);
    printf("%d\n", dep[root]);
    return 0;
}