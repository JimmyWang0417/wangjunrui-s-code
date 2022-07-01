#include <cstdio>
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
int n, m;
vector<int> g[N], h[N];
int dfn[N], low[N], dfstime;
int tot;
int st[N], top;
int a[N];
int sum;
inline void tarjan(int u)
{
    ++sum;
    dfn[u] = low[u] = ++dfstime;
    a[st[++top] = u] = -1;
    for (auto v : g[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            ckmin(low[u], low[v]);
            if (dfn[u] == low[v])
            {
                ++tot;
                h[tot].push_back(u);
                h[u].push_back(tot);
                a[tot] = 2;
                while (st[top] != v)
                {
                    h[tot].push_back(st[top]);
                    h[st[top]].push_back(tot);
                    ++a[tot];
                    --top;
                }
                h[tot].push_back(v);
                h[v].push_back(tot);
                --top;
            }
        }
        else
            ckmin(low[u], dfn[v]);
    }
}
int size[N];
ll answer;
inline void dfs(int u, int _fa)
{
    size[u] = (u <= n);
    for (auto v : h[u])
    {
        if (v == _fa)
            continue;
        dfs(v, u);
        answer += 2ll * size[u] * size[v] * a[u];
        size[u] += size[v];
    }
    answer += 2ll * size[u] * (sum - size[u]) * a[u];
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    tot = n;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
        {
            tarjan(i);
            dfs(i, 0);
            sum = 0;
        }
    printf("%lld\n", answer);
    return 0;
}