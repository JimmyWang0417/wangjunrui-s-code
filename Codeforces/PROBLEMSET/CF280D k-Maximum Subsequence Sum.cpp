/**
 *    unicode: UTF-8
 *    name:    CF280D k-Maximum Subsequence Sum
 *    author:  whitepaperdog
 *    created: 2022.07.20 周三 14:53:19 (Asia/Shanghai)
 **/
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
constexpr int N = 1e5 + 5;
int n, m;
struct node
{
    int x, l, r;
    node(int _x = 0, int _l = 0, int _r = 0) : x(_x), l(_l), r(_r) {}
    inline node operator+(const node &rhs) const
    {
        return node(x + rhs.x, l, rhs.r);
    }
    inline bool operator<(const node &rhs) const
    {
        return x < rhs.x;
    }
};
struct Node
{
    node ans, pre, suf, sum;
    Node(node _ans = node(), node _pre = node(), node _suf = node(), node _sum = node()) : ans(_ans), pre(_pre), suf(_suf), sum(_sum) {}
    inline Node operator+(const Node &rhs) const
    {
        return Node(max(max(ans, rhs.ans), suf + rhs.pre),
                    max(pre, sum + rhs.pre),
                    max(suf + rhs.sum, rhs.suf),
                    sum + rhs.sum);
    }
};
struct Tree
{
    Node res, opp;
    bool rev;
    inline void init(int pos, int val)
    {
        res = Node(node(val, pos, pos), node(val, pos, pos), node(val, pos, pos), node(val, pos, pos));
        opp = Node(node(-val, pos, pos), node(-val, pos, pos), node(-val, pos, pos), node(-val, pos, pos));
    }
    inline void reverse()
    {
        swap(res, opp);
        rev ^= 1;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].res = tree[lc].res + tree[rc].res;
    tree[rt].opp = tree[lc].opp + tree[rc].opp;
}
inline void pushdown(int rt)
{
    if (tree[rt].rev)
    {
        tree[lc].reverse();
        tree[rc].reverse();
        tree[rt].rev = false;
    }
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        int val;
        read(val);
        tree[rt].init(l, val);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].init(l, val);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline void reverse(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt].reverse();
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (x <= mid)
        reverse(lc, l, mid, x, y);
    if (y > mid)
        reverse(rc, mid + 1, r, x, y);
    pushup(rt);
}
inline Node query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[rt].res;
    int mid = (l + r) >> 1;
    pushdown(rt);
    if (y <= mid)
        return query(lc, l, mid, x, y);
    if (x > mid)
        return query(rc, mid + 1, r, x, y);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
pair<int, int> st[N];
int top;
signed main()
{
    read(n);
    build(1, 1, n);
    read(m);
    while (m--)
    {
        int opt, l, r, x;
        read(opt, l, r);
        if (opt)
        {
            read(x);
            int res = 0;
            while (x--)
            {
                node now = query(1, 1, n, l, r).ans;
                if (now.x <= 0)
                    break;
                res += now.x;
                reverse(1, 1, n, now.l, now.r);
                st[++top] = make_pair(now.l, now.r);
            }
            while (top)
            {
                reverse(1, 1, n, st[top].first, st[top].second);
                --top;
            }
            printf("%d\n", res);
        }
        else
            update(1, 1, n, l, r);
    }
    return 0;
}