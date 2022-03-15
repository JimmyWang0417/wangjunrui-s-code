#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
using namespace std;
const int N = 1e5 + 5;
struct node
{
    int d, p, l;
    inline bool operator>(const node &rhs) const
    {
        return d > rhs.d;
    }
} a[N];
int n, m;
struct Tree
{
    int l, r;
    ll size, sum;
} tree[N * 40];
int root[N], cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void update(int pre, int &rt, int l, int r, int pos, int val1, ll val2)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    tree[rt].size += val1;
    tree[rt].sum += val2;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos, val1, val2);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos, val1, val2);
}
inline ll query(int rt, int l, int r, ll k_th)
{
    if (l == r)
        return tree[rt].sum / tree[rt].size * k_th;
    int mid = (l + r) >> 1;
    if (k_th <= tree[lc(rt)].size)
        return query(lc(rt), l, mid, k_th);
    else
        return tree[lc(rt)].sum + query(rc(rt), mid + 1, r, k_th - tree[lc(rt)].size);
}
int p[N], tot;
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].d, a[i].p, a[i].l);
        p[++tot] = a[i].p;
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    sort(a + 1, a + 1 + n, greater<node>());
    for (int i = a[1].d, j = 1; i >= 1; --i)
    {
        root[i] = root[i + 1];
        while (a[j].d == i && j <= n)
        {
            update(root[i], root[i], 1, tot, (int)(lower_bound(p + 1, p + 1 + tot, a[j].p) - p), a[j].l, (ll)a[j].l * a[j].p);
            ++j;
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        ll g, L;
        read(g, L);
        int l = 1, r = a[1].d, ans = -1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (tree[root[mid]].size >= L && query(root[mid], 1, tot, L) <= g)
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}