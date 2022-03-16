#include <cstdio>
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
constexpr int mod = 1e9 + 7;
int n, a[N];
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
struct node
{
    int min;
    int cnt;
    inline node operator+(const node &rhs) const
    {
        node ans = (*this);
        if (min > rhs.min)
            ans = rhs;
        else if (min == rhs.min)
            add(ans.cnt, rhs.cnt);
        return ans;
    }
};
struct Tree
{
    node res;
    int tag;
    inline void update(int val)
    {
        add(tag, val);
        res.min += val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].res = tree[lc].res + tree[rc].res;
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
        tree[rt].res.min = l;
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
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        add(tree[rt].res.cnt, val);
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
inline void print(int rt, int l, int r, int pos)
{
    if (l == r)
    {
        printf("%d %d\n", tree[rt].res.min, tree[rt].res.cnt);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    print(lc, l, mid, pos);
    print(rc, mid + 1, r, pos);
}
int st1[N], top1;
int st2[N], top2;
int dp[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("divide.in", "r", stdin);
    freopen("divide.out", "w", stdout);
#endif
    read(n);
    build(1, 1, n);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        update(1, 1, n, i, dp[i - 1]);
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
        dp[i] = (tree[1].res.min == i ? tree[1].res.cnt : 0);
    }
    printf("%d\n", dp[n]);
    return 0;
}
