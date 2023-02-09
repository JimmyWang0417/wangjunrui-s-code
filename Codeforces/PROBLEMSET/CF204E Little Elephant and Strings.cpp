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
struct Point
{
    int ch[26];
    int fa, len;
    int size, id;
} point[N];
int tot = 1, las = 1;
inline int insert(int c, int id)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
    for (p = np; p && point[p].id != id; p = point[p].fa)
    {
        ++point[p].size;
        point[p].id = id;
    }
    return np;
}
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
int n, k;
char str[N];
vector<int> g[N];
int dp[N];
inline void dfs(int u)
{
    if (point[u].size >= k)
        dp[u] += point[u].len - point[point[u].fa].len;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dp[v] = dp[u];
        dfs(v);
    }
}
signed main()
{
    read(n, k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str);
        for (int j = 0; str[j]; ++j)
            g[i].push_back(insert(str[j] - 'a', i));
        las = 1;
    }
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1);
    for (int i = 1; i <= n; ++i)
    {
        ll res = 0;
        for (auto u : g[i])
            res += dp[u];
        printf("%lld ", res);
    }
    return 0;
}