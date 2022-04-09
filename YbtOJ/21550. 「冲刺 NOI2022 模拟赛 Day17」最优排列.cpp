#include <algorithm>
#include <climits>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <list>
#include <set>
#include <vector>
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
constexpr int N = 1e5 + 5;
int n, p[N];
pair<int, int> a[N];
int mp[N];
list<int> g[N];
struct Tree
{
    int min, pos;
    int tag;
    set<int> se;
    inline void update(int val)
    {
        min += val;
        tag += val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].min = tree[lc].min;
    tree[rt].pos = tree[lc].pos;
    if (tree[lc].min > tree[rc].min)
    {
        tree[rt].min = tree[rc].min;
        tree[rt].pos = tree[rc].pos;
    }
}
inline void pushdown(int rt)
{
    if (tree[rt].tag)
    {
        tree[lc].update(tree[rt].tag);
        tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].min = l - mp[l];
        tree[rt].pos = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline pair<int, int> find(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return make_pair(INT_MAX, 0);
    if (x <= l && r <= y)
        return make_pair(tree[rt].min, tree[rt].pos);
    int mid = (l + r) >> 1;
    pushdown(rt);
    pair<int, int> res = find(lc, l, mid, x, y), now = find(rc, mid + 1, r, x, y);
    if (res.first > now.first)
        res = now;
    return res;
}
inline void insert(int rt, int l, int r, int pos, int id)
{
    tree[rt].se.insert(id);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        insert(lc, l, mid, pos, id);
    else
        insert(rc, mid + 1, r, pos, id);
}
inline void del(int rt, int l, int r, int pos, int id)
{
    tree[rt].se.erase(id);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        del(lc, l, mid, pos, id);
    else
        del(rc, mid + 1, r, pos, id);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return INT_MAX;
    if (x <= l && r <= y)
        return tree[rt].se.empty() ? INT_MAX : *tree[rt].se.begin();
    int mid = (l + r) >> 1;
    return min(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
inline void check()
{
    __gnu_pbds::priority_queue<int, greater<int>> q;
    for (int i = 1; i <= n; ++i)
    {
        for (auto u : g[i])
            q.push(a[u].second);
        if (q.empty() || q.top() < i)
        {
            printf("-1\n");
            exit(0);
        }
        else
            q.pop();
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("prophesy.in", "r", stdin);
    freopen("prophesy.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].first, a[i].second);
        ++mp[a[i].second];
        g[a[i].first].push_back(i);
    }
    check();
    for (int i = 1; i <= n; ++i)
        mp[i] += mp[i - 1];
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        int pos = find(1, 1, n, i, n).second;
        for (auto u : g[i])
            insert(1, 1, n, a[u].second, u);
        p[i] = query(1, 1, n, i, pos);
        del(1, 1, n, a[p[i]].second, p[i]);
        update(1, 1, n, i, a[p[i]].second - 1, -1);
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", p[i]);
    putchar('\n');
    return 0;
}
