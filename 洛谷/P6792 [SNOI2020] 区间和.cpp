/**
 *    unicode: UTF-8
 *    name:    P6792 [SNOI2020] 区间和
 *    author:  whitepaperdog
 *    created: 2022.08.22 周一 20:26:24 (Asia/Shanghai)
 **/
#include <algorithm>
#include <climits>
#include <cstdio>
#define int ll
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
constexpr int INF = 0x7fffffff;
int n, q;
struct node
{
    int val, cnt;
    ll sum;
    node(int _val = 0, int _cnt = 0, ll _sum = 0) : val(_val), cnt(_cnt), sum(_sum) {}
    inline int calc(int pos) const
    {
        return pos == val ? cnt : 0;
    }
    inline void update(int x, int y)
    {
        if (x == val)
        {
            val += y;
            sum += (ll)y * cnt;
        }
    }
    inline bool operator<(const node &rhs) const
    {
        return sum == rhs.sum ? cnt < rhs.cnt : sum < rhs.sum;
    }
    inline node operator+(const node &rhs) const
    {
        node res;
        res.val = min(val, rhs.val);
        res.sum = sum + rhs.sum;
        res.cnt = calc(res.val) + rhs.calc(res.val);
        return res;
    }
};
inline int calc(const node &x, const node &y, const node &z, int v)
{
    ll s = x.sum - y.sum - z.sum;
    int d = -x.calc(v) + y.calc(v) + z.calc(v);
    if (s > 0 && d)
        return (int)min((ll)INF, s / d + 1 + v);
    return INF;
}
struct Tree
{
    int first, second;
    int val, tag;
    node pre, suf, ans, sum;
    inline void init(int x)
    {
        first = x, second = INF;
        sum = node(x, 1, x);
        if (x > 0)
        {
            pre = suf = ans = node(x, 1, x);
            val = INF;
        }
        else if (x == 0)
        {
            pre = suf = ans = node(x, 1, x);
            val = 1;
        }
        else
        {
            pre = suf = ans = node(INF, 0, 0);
            val = 1;
        }
    }
    inline void update(int x)
    {
        pre.update(first, x);
        suf.update(first, x);
        ans.update(first, x);
        sum.update(first, x);
        tag += x;
        first += x;
    }

    inline Tree operator+(const Tree &rhs) const
    {
        static Tree res;
        res.ans = max(max(ans, rhs.ans), suf + rhs.pre);
        res.sum = sum + rhs.sum;
        res.pre = max(pre, sum + rhs.pre);
        res.suf = max(suf + rhs.sum, rhs.suf);
        if (first < rhs.first)
        {
            res.first = first;
            res.second = min(second, rhs.first);
        }
        else if (first > rhs.first)
        {
            res.first = rhs.first;
            res.second = min(first, rhs.second);
        }
        else
        {
            res.first = first;
            res.second = min(second, rhs.second);
        }
        res.val = min(min(val, rhs.val),
                      min(calc(pre, sum, rhs.pre, res.first), calc(rhs.suf, suf, rhs.sum, res.first)));
        return res;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt] = tree[lc] + tree[rc];
}
inline void pushdown(int rt)
{
    if (tree[rt].tag)
    {
        int val = tree[rt].first - tree[rt].tag;
        if (tree[lc].first == val)
            tree[lc].update(tree[rt].tag);
        if (tree[rc].first == val)
            tree[rc].update(tree[rt].tag);
        tree[rt].tag = 0;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        int x;
        read(x);
        tree[rt].init(x);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void dfs(int rt, int l, int r, int val)
{
    if (val <= tree[rt].first)
        return;
    if (l == r)
        return tree[rt].init(val);
    if (val < tree[rt].val && val < tree[rt].second)
        return tree[rt].update(val - tree[rt].first);
    int mid = (l + r) >> 1;
    pushdown(rt);
    dfs(lc, l, mid, val);
    dfs(rc, mid + 1, r, val);
    pushup(rt);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return dfs(rt, l, r, val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update(lc, l, mid, x, y, val);
    update(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline Tree query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (y <= mid)
        return query(lc, l, mid, x, y);
    if (x > mid)
        return query(rc, mid + 1, r, x, y);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n, q);
    build(1, 1, n);
    for (int i = 1; i <= q; ++i)
    {
        int opt, l, r, x;
        read(opt, l, r);
        if (!opt)
        {
            read(x);
            update(1, 1, n, l, r, x);
        }
        else
            printf("%lld\n", query(1, 1, n, l, r).ans.sum);
    }
    return 0;
}