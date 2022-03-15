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
const int N = 6e6 + 5;
struct Point
{
    map<int, int> ch;
    int fa, len;
} point[N];
int tot = 1, las = 1;
int dp[N];
inline void insert(int c, int v)
{
    int p = las, np = las = ++tot;
    dp[np] = v;
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
int q[N];
int a[N], cnt;
inline void work(char *str)
{
    int len = (int)strlen(str);
    ll ans = 0;
    int u = 1;
    for (int i = 0; i < len; ++i)
    {
        if (!u)
            u = 1;
        u = point[u].ch[str[i] - 'a'];
    }
    if (point[u].len >= len)
        a[cnt = 1] = u;
    else
        cnt = 0;
    for (int i = 0; i < len - 1; ++i)
    {
        while (len - 1 <= point[point[u].fa].len)
            u = point[u].fa;
        u = point[u].ch[str[i] - 'a'];
        if (len <= point[u].len)
            a[++cnt] = u;
    }
    sort(a + 1, a + 1 + cnt);
    cnt = (int)(unique(a + 1, a + 1 + cnt) - a - 1);
    for (int i = 1; i <= cnt; ++i)
        ans += dp[a[i]];
    printf("%lld\n", ans);
}
char str[N];
int id[N];
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
inline void dfs(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
        dp[u] += dp[v];
    }
}
signed main()
{
    scanf("%s", str);
    for (int i = 0; str[i]; ++i)
        insert(str[i] - 'a', 1);
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        id[i] = m;
        char *s = str + m;
        scanf("%s", s);
        int len = (int)strlen(s);
        m += len + 1;
        las = 1;
        for (int j = 0; j < len; ++j)
            insert(s[j] - 'a', 0);
        for (int j = 0; j < len - 1; ++j)
            insert(s[j] - 'a', 0);
    }
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1);
    for (int i = 1; i <= n; ++i)
        work(str + id[i]);
    return 0;
}