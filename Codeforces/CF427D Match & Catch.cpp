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
const int N = 2e4 + 5;
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
template <typename T>
inline void ckmin(T &x, T y)
{
    if (x > y)
        x = y;
}
struct Point
{
    int ch[26];
    int fa, len;
    int id, size;
} point[N];
int tot = 1, las = 1;
int dp[N];
inline void insert(int c, int id)
{
    int p = las, np = las = ++tot;
    dp[np] = 1;
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
inline void dfs(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
        dp[u] += dp[v];
    }
}
char str[N];
signed main()
{
    scanf("%s", str);
    for (int i = 0; str[i]; ++i)
        insert(str[i] - 'a', 1);
    scanf("%s", str);
    las = 1;
    for (int i = 0; str[i]; ++i)
        insert(str[i] - 'a', 2);
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1);
    int ans = 0x3f3f3f3f;
    for (int i = 2; i <= tot; ++i)
        if (dp[i] == 2 && point[i].size == 2)
            ckmin(ans, point[point[i].fa].len + 1);
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}