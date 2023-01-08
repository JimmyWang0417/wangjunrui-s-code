#include <algorithm>
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
constexpr int N = 3e5 + 5;
int n, m;
int a[N];
struct node
{
    int l, r;
    int w, id;
    inline bool operator<(const node &rhs) const
    {
        return w > rhs.w;
    }
} b[N];
ll sum[N];
struct recover
{
    ll l, r;
    int w, id;
} c[N];
int tot;
struct Tree
{
    ll left, right;
    int tot;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void build(int rt, int l, int r)
{
    tree[rt].left = tree[rt].right = -1e18;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline bool update(int rt, int l, int r, const node &pos)
{
    c[++tot] = (recover){tree[rt].left, tree[rt].right, tree[rt].tot, rt};
    if (l == r)
    {
        tree[rt].left = 1 + sum[pos.l - 1];
        tree[rt].right = 1 - sum[pos.r];
        tree[rt].tot = 1;
        return sum[pos.l - 1] < sum[pos.r];
    }
    int mid = (l + r) >> 1;
    bool res;
    if (pos.id <= mid)
        res = update(lc, l, mid, pos);
    else
        res = update(rc, mid + 1, r, pos);
    tree[rt].left = max(tree[lc].left + tree[rc].tot, tree[rc].left);
    tree[rt].right = max(tree[lc].right, tree[lc].tot + tree[rc].right);
    tree[rt].tot = tree[lc].tot + tree[rc].tot;
    return res && tree[lc].left + tree[rc].right <= 0;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("azls.in", "r", stdin);
    freopen("azls.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 1; i <= m; ++i)
    {
        read(b[i].l, b[i].r, b[i].w);
        b[i].id = i;
    }
    sort(b + 1, b + 1 + m);
    ll answer = 0;
    build(1, 1, m);
    for (int i = 1; i <= m; ++i)
    {
        tot = 0;
        if (update(1, 1, m, b[i]))
            answer += b[i].w;
        else
        {
            for (int j = 1; j <= tot; ++j)
                tree[c[j].id] = (Tree){c[j].l, c[j].r, c[j].w};
        }
    }
    printf("%lld\n", answer);
    return 0;
}
