#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e6 + 5;
int n;
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
struct Point
{
    int ch[26], fa;
    int len;
} point[N];
int las = 1, tot = 1;
inline void insert(int c)
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
}
int exist[N];
int dp[N];
inline void dfs(int u, int maxx = 0)
{
    if (exist[u])
        maxx = exist[u];
    dp[u] = maxx;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v, maxx);
    }
}
char str[N];
int where[N];
pair<int, int> a[N];
int m;
signed main()
{
    read(n);
    scanf("%s", str + 1);
    int len = (int)strlen(str + 1);
    for (int i = 1; str[i]; ++i)
    {
        insert(str[i] - 'a');
        where[i] = las;
    }
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str + 1);
        int u = 1;
        for (int j = 1; u && str[j]; ++j)
            u = point[u].ch[str[j] - 'a'];
        if (u)
            ckmax(exist[u], (int)strlen(str + 1));
    }
    dfs(1);
    for (int i = 1; i <= len; ++i)
        if (dp[where[i]])
            a[++m] = make_pair(i - dp[where[i]] + 1, i);
    sort(a + 1, a + 1 + m);
    int res = 0;
    for (int r = 1, mx = 0, id = 1; r <= len; r++)
    {
        if (id > m || a[id].first > r)
        {
            printf("-1\n");
            return 0;
        }
        while (a[id].first <= r && id <= m)
            ckmax(mx, a[id].second), ++id;
        r = mx, ++res;
    }
    printf("%d\n", res);
    return 0;
}