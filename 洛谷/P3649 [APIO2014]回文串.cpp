#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 3e5 + 5;
struct PAM
{
    int fa, len;
    int size;
    int ch[26];
} point[N];
int cnt = 1, las = 0;
int len, n;
char str[N];
inline int getfa(int x)
{
    while (str[n] != str[n - point[x].len - 1])
        x = point[x].fa;
    return x;
}
int f[N];
inline void insert(int c)
{
    int cur = getfa(las);
    int now = point[cur].ch[c];
    if (!now)
    {
        now = ++cnt;
        point[now].len = point[cur].len + 2;
        point[now].fa = point[getfa(point[cur].fa)].ch[c];
        point[cur].ch[c] = now;
    }
    ++f[now];
    las = now;
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
ll ans = 0;
inline void dfs(int u)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
        f[u] += f[v];
    }
    ans = max(ans, (ll)f[u] * point[u].len);
}
signed main()
{
    point[1].len = -1;
    point[1].fa = 0;
    point[0].fa = 1;
    scanf("%s", str + 1);
    len = (int)strlen(str + 1);
    for (n = 1; n <= len; ++n)
        insert(str[n] - 'a');
    for (int i = 2; i <= cnt; ++i)
        add_edge(point[i].fa, i);
    dfs(0), dfs(1);
    printf("%lld\n", ans);
    return 0;
}
