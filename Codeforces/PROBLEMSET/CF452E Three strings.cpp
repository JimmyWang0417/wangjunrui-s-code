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
const int N = 6e5 + 5;
const int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void del(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
struct Point
{
    int ch[26];
    int fa, len;
} point[N];
int tot = 1, las = 1;
int dp[3][N];
inline void insert(int c, int id)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    dp[id][np] = 1;
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
int answer[N];
int suf[N];
inline void dfs(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
        dp[0][u] += dp[0][v];
        dp[1][u] += dp[1][v];
        dp[2][u] += dp[2][v];
    }
    int res = (int)((ll)dp[0][u] * dp[1][u] * dp[2][u] % mod);
    add(suf[point[u].len], res);
    del(suf[point[point[u].fa].len], res);
}
char str[N];
signed main()
{
    scanf("%s", str);
    int minlen = (int)strlen(str);
    for (int i = 0; str[i]; ++i)
        insert(str[i] - 'a', 0);
    las = 1;
    scanf("%s", str);
    for (int i = 0; str[i]; ++i)
        insert(str[i] - 'a', 1);
    ckmin(minlen, (int)strlen(str));
    las = 1;
    scanf("%s", str);
    for (int i = 0; str[i]; ++i)
        insert(str[i] - 'a', 2);
    ckmin(minlen, (int)strlen(str));

    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1);
    for (int i = minlen - 1; i >= 1; --i)
        add(suf[i], suf[i + 1]);
    for (int i = 1; i <= minlen; ++i)
        printf("%d ", suf[i]);
    putchar('\n');
    return 0;
}