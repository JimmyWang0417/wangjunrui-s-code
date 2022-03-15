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
constexpr int N = 1e6 + 5;
int n, m, k;
struct Tree
{
    int sum;
    bool flag;
    inline void cover()
    {
        sum = 0;
        flag = true;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
}
inline void pushdown(int rt)
{
    if (tree[rt].flag)
    {
        tree[lc].cover();
        tree[rc].cover();
        tree[rt].flag = false;
    }
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].sum += val;
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
inline void cover(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
    {
        tree[rt].cover();
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    cover(lc, l, mid, x, y);
    cover(rc, mid + 1, r, x, y);
    pushup(rt);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
struct node
{
    int opt, x, l, r, id;
    inline bool operator<(const node &rhs) const
    {
        return x == rhs.x ? opt < rhs.opt : x > rhs.x;
    }
} a[N];
int tot = 0, maxx = 0;
set<int> se;
int need[N], answer[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("treasure.in","r",stdin);
    freopen("treasure.out","w",stdout);
#endif
    read(k);
    for (int i = 1; i <= k; ++i)
    {
        int x1, y1, x2, y2;
        read(x1, y1, x2, y2);
        a[++tot] = (node){1, x2, y1, y2, i};
        a[++tot] = (node){2, x1 - 1, y1, y2, i};
        ckmax(maxx, y2);
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        a[++tot] = (node){3, x, y, 0, 0};
        ckmax(maxx, y);
    }
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        read(x, y);
        a[++tot] = (node){4, x, y, 0, i};
        ckmax(maxx, y);
    }
    ++maxx;
    sort(a + 1, a + 1 + tot);
    se.insert(maxx);
    for (int i = 1; i <= tot; ++i)
    {
        if (a[i].opt == 1)
        {
            int nxt = (*se.upper_bound(a[i].r));
            need[a[i].id] = query(1, 0, maxx, a[i].r + 1, nxt);
            update(1, 0, maxx, a[i].l - 1, query(1, 0, maxx, a[i].l, nxt));
            cover(1, 0, maxx, a[i].l, a[i].r);
            se.insert(a[i].l - 1);
            se.insert(a[i].r);
        }
        else if (a[i].opt == 2)
        {
            update(1, 0, maxx, a[i].l - 1, -need[a[i].id]);
            cover(1, 0, maxx, a[i].l, a[i].r);
            se.erase(se.find(a[i].l - 1));
            se.erase(se.find(a[i].r));
        }
        else if (a[i].opt == 3)
            update(1, 0, maxx, a[i].l, 1);
        else
        {
            int nxt = (*se.lower_bound(a[i].l));
            answer[a[i].id] = query(1, 0, maxx, a[i].l, nxt);
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", answer[i]);
    return 0;
}