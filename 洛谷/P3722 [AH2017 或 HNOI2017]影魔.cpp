#include <algorithm>
#include <cstdio>
#include <vector>
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
constexpr int N = 2e5 + 5;
int n, m, p1, p2;
int a[N], b[N];
int id[N];
struct node
{
    int l, r, id;
    inline bool operator<(const node &rhs) const
    {
        return l < rhs.l;
    }
    inline bool operator>(const node &rhs) const
    {
        return r > rhs.r;
    }
} q[N];
ll answer[N];
int st[N], top;
namespace subtask1
{
    struct tree_array
    {
        int sum[N];
        inline void update(int pos)
        {
            for (int i = pos; i; i -= lowbit(i))
                ++sum[i];
        }
        inline int query(int pos)
        {
            int res = 0;
            for (int i = pos; i <= n; i += lowbit(i))
                res += sum[i];
            return res;
        }
    } tree;
    inline void solve()
    {
        top = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (top && a[i] >= a[st[top]])
                --top;
            b[i] = st[top];
            st[++top] = i;
        }
        sort(q + 1, q + 1 + m, [](const node &x, const node &y)
             { return x.r < y.r; });
        for (int i = 1, j = 1; i <= n; ++i)
        {
            tree.update(b[i]);
            while (j <= m && i == q[j].r)
            {
                answer[q[j].id] += (ll)tree.query(q[j].l) * p1;
                ++j;
            }
        }
    }
}
namespace subtask2
{
    struct tree_array
    {
        int sum[N];
        inline void update(int pos)
        {
            for (int i = pos; i <= n; i += lowbit(i))
                ++sum[i];
        }
        inline int query(int pos)
        {
            int res = 0;
            for (int i = pos; i; i -= lowbit(i))
                res += sum[i];
            return res;
        }
    } tree;
    inline void solve()
    {
        top = 0;
        for (int i = n; i >= 1; --i)
        {
            while (top && a[i] >= a[st[top]])
                --top;
            b[i] = st[top];
            st[++top] = i;
        }
        sort(q + 1, q + 1 + m, [](const node &x, const node &y)
             { return x.l > y.l; });
        for (int i = n, j = 1; i >= 1; --i)
        {
            if (b[i])
                tree.update(b[i]);
            while (j <= m && i == q[j].l)
            {
                answer[q[j].id] += (ll)tree.query(q[j].r) * p1;
                ++j;
            }
        }
    }
}
namespace subtask3
{
    struct tree_array
    {
        ll sum1[N], sum2[N];
        inline void update(int pos, int val)
        {
            for (int i = pos; i <= n; i += lowbit(i))
            {
                sum1[i] += val;
                sum2[i] += (ll)pos * val;
            }
        }
        inline void update(int l, int r, int val)
        {
            update(l, val);
            update(r + 1, -val);
        }
        inline ll query(int pos)
        {
            ll res = 0;
            for (int i = pos; i; i -= lowbit(i))
                res += (ll)(pos + 1) * sum1[i] - sum2[i];
            return res;
        }
        inline ll query(int l, int r)
        {
            return query(r) - query(l - 1);
        }
    } tree;
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
    int dfn[N], low[N], dep[N];
    inline void dfs(int u)
    {
        dfn[u] = low[u] = u;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            dep[v] = dep[u] + 1;
            dfs(v);
            ckmax(low[u], low[v]);
        }
    }
    inline void solve()
    {
        top = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (top && a[i] >= a[st[top]])
                --top;
            add_edge(st[top], i);
            st[++top] = i;
        }
        sort(q + 1, q + 1 + m, [](const node &x, const node &y)
             { return x.l < y.l; });
        dfs(0);
        for (int i = 1; i <= n; ++i)
            tree.update(i, i, dep[i] - 1);
        for (int i = 1, j = 1; i <= n; ++i)
        {
            if (i > 1)
                tree.update(dfn[i - 1], low[i - 1], -1);
            while (j <= m && q[j].l == i)
            {
                answer[q[j].id] += (ll)tree.query(q[j].l, q[j].r) * p2;
                ++j;
            }
        }
    }
}
namespace subtask4
{
    struct tree_array
    {
        ll sum1[N], sum2[N];
        inline void update(int pos, int val)
        {
            for (int i = pos; i <= n; i += lowbit(i))
            {
                sum1[i] += val;
                sum2[i] += (ll)pos * val;
            }
        }
        inline void update(int l, int r, int val)
        {
            update(l, val);
            update(r + 1, -val);
        }
        inline ll query(int pos)
        {
            ll res = 0;
            for (int i = pos; i; i -= lowbit(i))
                res += (ll)(pos + 1) * sum1[i] - sum2[i];
            return res;
        }
        inline ll query(int l, int r)
        {
            return query(r) - query(l - 1);
        }
    } tree;
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
    int dfn[N], low[N], dep[N];
    inline void dfs(int u)
    {
        dfn[u] = low[u] = u;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            dep[v] = dep[u] + 1;
            dfs(v);
            ckmin(dfn[u], dfn[v]);
        }
    }
    inline void solve()
    {
        top = 0;
        for (int i = n; i >= 1; --i)
        {
            while (top && a[i] >= a[st[top]])
                --top;
            add_edge(st[top], i);
            st[++top] = i;
        }
        sort(q + 1, q + 1 + m, [](const node &x, const node &y)
             { return x.r > y.r; });
        dfs(0);
        for (int i = 1; i <= n; ++i)
            tree.update(i, i, dep[i] - 1);
        for (int i = n, j = 1; i >= 1; --i)
        {
            if (i < n)
                tree.update(dfn[i + 1], low[i + 1], -1);
            while (j <= m && q[j].r == i)
            {
                answer[q[j].id] += (ll)tree.query(q[j].l, q[j].r) * p2;
                ++j;
            }
        }
    }
}
signed main()
{
    read(n, m, p1, p2);
    p1 -= p2;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    subtask1::solve();
    subtask2::solve();
    subtask3::solve();
    subtask4::solve();
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}
