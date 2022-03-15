#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 2e5 + 25;
constexpr int mod = 1e9 + 7;
constexpr int base = 1331;
int n, m, S, T;
struct Edge
{
    int next, to, dis;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    edge[num_edge].dis = dis;
    head[from] = num_edge;
}
struct Tree
{
    int l, r;
    int size;
    int cnt;
    bool tag;
    ll hash;
    inline void update()
    {
        tag = true;
        cnt = size;
        hash = 0;
    }
} tree[N * 100];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N * 2], cnt;
ull power[N];
inline int newnode(int rt)
{
    ++cnt;
    tree[cnt] = tree[rt];
    return cnt;
}
inline void pushup(int rt)
{
    tree[rt].hash = (tree[lc(rt)].hash + power[tree[lc(rt)].size] * tree[rc(rt)].hash) % mod;
    tree[rt].cnt = tree[lc(rt)].cnt + tree[rc(rt)].cnt;
}
inline void pushdown(int rt)
{
    if (tree[rt].tag)
    {
        lc(rt) = newnode(lc(rt));
        tree[lc(rt)].update();
        rc(rt) = newnode(rc(rt));
        tree[rc(rt)].update();
        tree[rt].tag = false;
    }
}
inline void build0(int &rt, int l, int r)
{
    rt = newnode(0);
    tree[rt].size = r - l + 1;
    if (l == r)
    {
        tree[rt].hash = 0;
        tree[rt].cnt = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build0(lc(rt), l, mid);
    build0(rc(rt), mid + 1, r);
    pushup(rt);
}
inline void build1(int &rt, int l, int r)
{
    rt = newnode(0);
    tree[rt].size = r - l + 1;
    if (l == r)
    {
        tree[rt].hash = 1;
        tree[rt].cnt = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build1(lc(rt), l, mid);
    build1(rc(rt), mid + 1, r);
    pushup(rt);
}
inline void update0(int &rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return;
    rt = newnode(rt);
    if (x <= l && r <= y)
    {
        tree[rt].update();
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    update0(lc(rt), l, mid, x, y);
    update0(rc(rt), mid + 1, r, x, y);
    pushup(rt);
}
inline void update1(int &rt, int l, int r, int pos)
{
    rt = newnode(rt);
    if (l == r)
    {
        tree[rt].hash = 1;
        tree[rt].cnt = 0;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        update1(lc(rt), l, mid, pos);
    else
        update1(rc(rt), mid + 1, r, pos);
    pushup(rt);
}
inline bool campare(int rtl, int rtr, int l, int r)
{
    if (l == r)
        return tree[rtl].hash < tree[rtr].hash;
    int mid = (l + r) >> 1;
    pushdown(rtl), pushdown(rtr);
    if (tree[rc(rtl)].cnt == tree[rc(rtr)].cnt && tree[rc(rtl)].hash == tree[rc(rtr)].hash)
        return campare(lc(rtl), lc(rtr), l, mid);
    else
        return campare(rc(rtl), rc(rtr), mid + 1, r);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (!rt || r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].cnt;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
}
inline int query(int rt, int l, int r, int k_th)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (k_th <= tree[lc(rt)].cnt)
        return query(lc(rt), l, mid, k_th);
    else
        return query(rc(rt), mid + 1, r, k_th - tree[lc(rt)].cnt);
}
int limit;
struct node
{
    int rt, x;
    node(int _rt = 0, int _x = 0) : rt(_rt), x(_x) {}
    inline bool operator<(const node &rhs) const
    {
        return campare(rt, rhs.rt, 0, limit);
    }
    inline bool operator>(const node &rhs) const
    {
        return campare(rhs.rt, rt, 0, limit);
    }
};
inline void print(int rt, int l, int r)
{
    if (l == r)
    {
        printf("%lld", tree[rt].hash);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    print(rc(rt), mid + 1, r);
    print(lc(rt), l, mid);
}
bool vis[N];
int pre[N];
int st[N], top;
int nmsl[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("base.in", "r", stdin);
    freopen("base.out", "w", stdout);
#endif
    read(n, m, S, T);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        ckmax(limit, w);
    }
    limit += 20;
    power[0] = 1;
    for (int i = 1; i <= limit; ++i)
        power[i] = power[i - 1] * 2 % mod;
    build1(root[0], 0, limit);
    for (int i = 1; i <= n; ++i)
        root[i] = root[0];
    build0(root[S], 0, limit);
    priority_queue<node, vector<node>, greater<node>> q;
    q.push(node(root[S], S));
    while (!q.empty())
    {
        int u = q.top().x;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to, &w = edge[i].dis;
            root[i + n] = root[u];
            int where = query(root[i + n], 0, limit, query(root[i + n], 0, limit, 0, w - 1) + 1);
            if (where > w)
                update0(root[i + n], 0, limit, w, where - 1);
            update1(root[i + n], 0, limit, where);
            if (campare(root[i + n], root[v], 0, limit))
            {
                root[v] = root[i + n];
                pre[v] = u;
                nmsl[v] = i;
                q.push(node(root[v], v));
            }
        }
    }
    if (!tree[root[T]].cnt)
        printf("-1\n");
    else
    {
        printf("%llu\n", tree[root[T]].hash);
        for (int u = T; u != S; u = pre[u])
            st[++top] = u;
        st[++top] = S;
        printf("%d\n", top);
        while (top)
            printf("%d ", st[top--]);
        putchar('\n');
    }
    return 0;
}
