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
const int N = 2e5 + 5;
int n, m, T;
struct Point
{
    int x, y;
    inline bool operator<(const Point &rhs) const
    {
        return x < rhs.x;
    }
} point[N];
struct Tree_array
{
    int c[N * 5];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= T; i += lowbit(i))
            ckmax(c[i], val);
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            ckmax(res, c[i]);
        return res;
    }
} tree_array;
ll dp[N];
vector<int> g[N];
vector<int> tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    tree[rt].clear();
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int x, int y)
{
    if (point[g[y][r]].x <= point[x].x && point[g[y][l]].y <= point[x].y)
    {
        tree[rt].push_back(x);
        return;
    }
    if (point[g[y][l]].x > point[x].x || point[g[y][r]].y > point[x].y)
        return;
    int mid = (l + r) >> 1;
    update(lc, l, mid, x, y);
    update(rc, mid + 1, r, x, y);
}
inline void solve(int rt, int l, int r, int x, int y, int need)
{
    ll res = LONG_LONG_MAX;
    int where = 0;
    int mid = (l + r) >> 1;
    for (int i = x; i <= y; ++i)
    {
        ll now = dp[g[need][i]] + (ll)(point[tree[rt][mid]].x - point[g[need][i]].x) * (point[tree[rt][mid]].y - point[g[need][i]].y);
        if (now < res)
        {
            res = now;
            where = i;
        }
    }
    ckmin(dp[tree[rt][mid]], res);
    if (l < mid)
        solve(rt, l, mid - 1, where, y, need);
    if (mid < r)
        solve(rt, mid + 1, r, x, where, need);
}
inline void work(int rt, int l, int r, int x)
{
    if (!tree[rt].empty())
        solve(rt, 0, (int)tree[rt].size() - 1, l, r, x);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    work(lc, l, mid, x);
    work(rc, mid + 1, r, x);
}
signed main()
{
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdout);
    read(n, T);
    for (int i = 1; i <= n; ++i)
        read(point[i].x, point[i].y);
    sort(point + 1, point + n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int res = tree_array.query(point[i].y) + 1;
        ckmax(m, res);
        tree_array.update(point[i].y, res);
        g[res].push_back(i);
    }
    memset(dp, 0x3f, sizeof(dp));
    for (auto i : g[1])
        dp[i] = (ll)point[i].x * point[i].y;
    for (int i = 2; i <= m; ++i)
    {
        int size = (int)g[i - 1].size() - 1;
        build(1, 0, size);
        for (int j : g[i])
            update(1, 0, size, j, i - 1);
        work(1, 0, size, i - 1);
    }
    ll res = LONG_LONG_MAX;
    for (auto i : g[m])
        ckmin(res, dp[i] + (ll)(T - point[i].x) * (T - point[i].y));
    printf("%lld\n", res);
    return 0;
}