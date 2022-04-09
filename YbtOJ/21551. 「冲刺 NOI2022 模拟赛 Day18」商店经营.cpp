#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <list>
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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 6e6 + 5;
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
int a[N];
int cnt[N];
ll answer;
int father[N];
int fa[N];
inline int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void dfs(int u, int _fa)
{
    if (cnt[u])
        _fa = u;
    fa[u] = _fa;
    for (int e = head[u]; e; e = edge[e].next)
    {
        int &v = edge[e].to;
        dfs(v, _fa);
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("shop.in", "r", stdin);
    freopen("shop.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 2; i <= n; ++i)
    {
        read(father[i]);
        add_edge(++father[i], i);
    }
    cnt[0] = 1919810258;
    for (int i = 1; i <= m; ++i)
    {
        int u;
        read(u);
        ++cnt[u + 1];
    }
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    dfs(1, 0);
    for (int i = n; i >= 1; --i)
    {
        if (find(i))
        {
            answer += i - 1;
            if (!--cnt[find(i)])
                fa[find(i)] = find(father[find(i)]);
        }
    }
    printf("%lld\n", answer);
    return 0;
}
