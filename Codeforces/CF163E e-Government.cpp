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
const int N = 1e6 + 5;
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
char str[N];
int ch[N][26], nxt[N], tot;
inline int insert(char *s)
{
    int u = 0;
    for (int i = 0; s[i]; ++i)
    {
        int c = s[i] - 'a';
        if (!ch[u][c])
            ch[u][c] = ++tot;
        u = ch[u][c];
    }
    return u;
}
inline void build()
{
    queue<int, list<int>> q;
    for (int i = 0; i < 26; ++i)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i)
            if (ch[u][i])
            {
                nxt[ch[u][i]] = ch[nxt[u]][i];
                q.push(ch[u][i]);
            }
            else
                ch[u][i] = ch[nxt[u]][i];
    }
}
int dfn[N], low[N], dfstime;
int c[N];
inline void update(int pos, int val)
{
    for (int i = pos; i <= dfstime; i += lowbit(i))
        c[i] += val;
}
inline void update(int l, int r, int val)
{
    update(l, val);
    update(r + 1, -val);
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += c[i];
    return res;
}
inline void dfs(int u)
{
    dfn[u] = ++dfstime;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        dfs(v);
    }
    low[u] = dfstime;
}
int id[N];
bool exist[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%s", str);
        id[i] = insert(str);
    }
    build();
    for (int i = 1; i <= tot; ++i)
        add_edge(nxt[i], i);
    dfs(0);
    for (int i = 1; i <= m; ++i)
    {
        update(dfn[id[i]], low[id[i]], 1);
        exist[i] = true;
    }
    while (n--)
    {
        scanf("%s", str);
        if (str[0] == '?')
        {
            ll res = 0;
            int u = 0;
            for (int i = 1; str[i]; ++i)
            {
                u = ch[u][str[i] - 'a'];
                res += query(dfn[u]);
            }
            printf("%lld\n", res);
        }
        else
        {
            int x;
            sscanf(str + 1, "%d", &x);
            if (str[0] == '+')
            {
                if (!exist[x])
                {
                    update(dfn[id[x]], low[id[x]], 1);
                    exist[x] = true;
                }
            }
            else if (exist[x])
            {
                update(dfn[id[x]], low[id[x]], -1);
                exist[x] = false;
            }
        }
    }
    return 0;
}