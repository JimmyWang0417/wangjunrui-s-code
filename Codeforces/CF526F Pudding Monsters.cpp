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
constexpr int N = 3e5 + 5;
int n, a[N];
int st1[N], top1;
int st2[N], top2;
struct Tree
{
    int min, cnt, tag;
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
    tree[rt].cnt = tree[lc].cnt;
    if (tree[rt].min > tree[rc].min)
    {
        tree[rt].min = tree[rc].min;
        tree[rt].cnt = tree[rc].cnt;
    }
    else if (tree[rt].min == tree[rc].min)
        tree[rt].cnt += tree[rc].cnt;
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].cnt = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
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
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].min ? 0 : tree[rt].cnt;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        read(x, y);
        a[x] = y;
    }
    build(1, 1, n);
    ll answer = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (top1 && a[st1[top1]] > a[i])
        {
            update(1, 1, n, st1[top1 - 1] + 1, st1[top1], a[st1[top1]] - a[i]);
            --top1;
        }
        st1[++top1] = i;
        while (top2 && a[st2[top2]] < a[i])
        {
            update(1, 1, n, st2[top2 - 1] + 1, st2[top2], a[i] - a[st2[top2]]);
            --top2;
        }
        st2[++top2] = i;
        update(1, 1, n, 1, i - 1, -1);
        answer += query(1, 1, n, 1, i);
    }
    printf("%lld\n", answer);
    return 0;
}