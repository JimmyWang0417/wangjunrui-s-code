/**
 *    unicode: UTF-8
 *    name:    SP11414 COT3 - Combat on a tree
 *    author:  wangjunrui
 *    created: 2022.08.05 周五 16:03:54 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
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
constexpr int N = 1e5 + 5;
int n, a[N];
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int dep[N * 21];
int tag[N * 21];
int ch[N * 21][2];
bool full[N * 21];
int root[N], tot;
#define lc(rt) ch[rt][0]
#define rc(rt) ch[rt][1]
inline void pushup(int rt)
{
    full[rt] = (full[lc(rt)] && full[rc(rt)]);
}
inline void pushtag(int rt, int val)
{
    if (!rt)
        return;
    tag[rt] ^= val;
    if (val >> dep[rt] & 1)
        swap(lc(rt), rc(rt));
}
inline void pushdown(int rt)
{
    if (tag[rt])
    {
        pushtag(lc(rt), tag[rt]);
        pushtag(rc(rt), tag[rt]);
        tag[rt] = 0;
    }
}
inline void insert(int &rt, int val, int _dep = 20)
{
    if (!rt)
        dep[rt = ++tot] = _dep;
    if (_dep == -1)
    {
        full[rt] = true;
        return;
    }
    pushdown(rt);
    insert(ch[rt][val >> _dep & 1], val, _dep - 1);
    pushup(rt);
}
inline int merge(int x, int y)
{
    if (!x || full[y])
        return y;
    if (!y || full[x])
        return x;
    pushdown(x), pushdown(y);
    lc(x) = merge(lc(x), lc(y));
    rc(x) = merge(rc(x), rc(y));
    pushup(x);
    return x;
}
inline int query(int rt)
{
    int res = 0;
    for (int i = 20; i >= 0 && rt; --i)
    {
        pushdown(rt);
        if (!full[lc(rt)])
            rt = lc(rt);
        else
        {
            res |= 1 << i;
            rt = rc(rt);
        }
    }
    return res;
}
int dp[N];
inline void dfs(int u, int _fa)
{
    int sum = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u);
        sum ^= dp[v];
    }
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        pushtag(root[v], sum ^ dp[v]);
        root[u] = merge(root[u], root[v]);
    }
    if (!a[u])
        insert(root[u], sum);
    dp[u] = query(root[u]);
}
int answer[N], answertot;
inline void dfs(int u, int _fa, int out)
{
    int sum = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        sum ^= dp[v];
    }
    if (!a[u] && (out ^ sum) == 0)
        answer[++answertot] = u;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        dfs(v, u, out ^ sum ^ dp[v]);
    }
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    dfs(1, 0, 0);
    if (answertot)
    {
        sort(answer + 1, answer + 1 + answertot);
        for (int i = 1; i <= answertot; ++i)
            printf("%d\n", answer[i]);
    }
    else
        printf("-1\n");
    return 0;
}