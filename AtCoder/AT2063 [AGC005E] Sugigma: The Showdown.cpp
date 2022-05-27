#include <cstdio>
#include <cstdlib>
#include <vector>
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
constexpr int N = 2e5 + 5;
int n, rootx, rooty;
vector<int> g[N], h[N];
pair<int, int> p[N];
int fa[N], dep[N];
bool exist[N];
inline void init(int u, int _fa)
{
    fa[u] = _fa;
    for (auto v : h[u])
    {
        if (v == _fa)
            continue;
        dep[v] = dep[u] + 1;
        init(v, u);
    }
}
inline bool check(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    if (dep[u] == dep[v])
        return fa[u] != fa[v];
    else if (dep[u] == dep[v] + 1)
        return fa[u] != v;
    else if (dep[u] == dep[v] + 2)
        return fa[fa[u]] != v;
    else
        return true;
}
int answer;
inline void dfs(int u, int _fa, int depf)
{
    if (depf >= dep[u])
        return;
    if (exist[u])
    {
        printf("-1\n");
        exit(0);
    }
    ckmax(answer, dep[u]);
    for (auto v : g[u])
    {
        if (v == _fa)
            continue;
        dfs(v, u, depf + 1);
    }
}
signed main()
{
    read(n, rootx, rooty);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
        p[i] = make_pair(u, v);
    }
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        h[u].push_back(v);
        h[v].push_back(u);
    }
    init(rooty, 0);
    for (int i = 1; i < n; ++i)
        if (check(p[i].first, p[i].second))
            exist[p[i].first] = exist[p[i].second] = true;
    dfs(rootx, 0, 0);
    printf("%d\n", answer * 2);
    return 0;
}