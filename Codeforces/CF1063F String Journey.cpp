// Problem: F. String Journey
// Contest: Codeforces - Codeforces Round #516 (Div. 1, by Moscow Team Olympiad)
// URL: https://codeforces.com/problemset/problem/1063/F
// Memory Limit: 512 MB
// Time Limit: 5000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 1e6 + 6;
int n;
char str[N];
struct Point
{
    int ch[26], fa, len;
} point[N];
int las = 1, tot = 1;
int id[N];
inline int insert(int c)
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
int dfn[N], low[N], dfstime;
int fa[N][25];
inline void dfs(int u)
{
    for (int i = 0; i < 20; ++i)
        fa[u][i + 1] = fa[fa[u][i]][i];
    dfn[u] = ++dfstime;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        fa[v][0] = u;
        dfs(v);
    }
    low[u] = dfstime;
}
inline int get(int u, int len)
{
    for (int i = 20; i >= 0; --i)
        if (point[fa[u][i]].len >= len)
            u = fa[u][i];
    return u;
}
int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt] = max(tree[lc], tree[rc]);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return INT_MIN;
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    return max(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
int dp[N];
inline bool check(int u)
{
    int x = get(id[u], dp[u] - 1);
    if (query(1, 1, dfstime, dfn[x], low[x]) >= dp[u] - 1)
        return true;
    x = get(id[u - 1], dp[u] - 1);
    if (query(1, 1, dfstime, dfn[x], low[x]) >= dp[u] - 1)
        return true;
    return false;
}
signed main()
{
    read(n);
    scanf("%s", str + 1);
    reverse(str + 1, str + 1 + n);
    point[0].len = -1;
    for (int i = 1; i <= n; ++i)
        id[i] = insert(str[i] - 'a');
    for (int i = 2; i <= tot; ++i)
        add_edge(point[i].fa, i);
    dfs(1);
    int res = 0;
    for (int i = 1, now = 0; i <= n; ++i)
    {
        dp[i] = dp[i - 1] + 1;
        while (!check(i))
        {
            --dp[i];
            ++now;
            update(1, 1, dfstime, dfn[id[now]], dp[now]);
        }
        ckmax(res, dp[i]);
    }
    printf("%d\n", res);
    return 0;
}