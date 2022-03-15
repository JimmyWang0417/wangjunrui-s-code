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
inline int calc(char c)
{
    return c == 'A' ? 0 : (c == 'T' ? 1 : (c == 'G' ? 2 : 3));
}
struct SAM
{
    int ch[4], fa;
    int len;
} point[N];
int las = 1, tot = 1;
int f[N];
inline void insert(int c)
{
    int p = las, np = las = ++tot;
    f[np] = 1;
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
        f[u] += f[v];
    }
}
char str0[N], str[N];
int len;
int answer;
inline void calc(int u, int pos, int used)
{
    if (pos > len)
    {
        answer += f[u];
        return;
    }
    for (int c = 0; c < 4; ++c)
    {
        int v = point[u].ch[c];
        if (!v)
            continue;
        if (calc(str[pos]) == c)
            calc(v, pos + 1, used);
        else if (used < 3)
            calc(v, pos + 1, used + 1);
    }
}
inline void work()
{
    scanf("%s%s", str0 + 1, str + 1);
    len = (int)strlen(str + 1);
    for (int i = 1; str0[i]; ++i)
        insert(calc(str0[i]));
    for (int i = 1; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1);
    calc(1, 1, 0);
    printf("%d\n", answer);
    answer = 0;
    memset(head, num_edge = 0, sizeof(head));
    memset(f, 0, sizeof(f));
    tot = las = 1;
    memset(point, 0, sizeof(point));
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}