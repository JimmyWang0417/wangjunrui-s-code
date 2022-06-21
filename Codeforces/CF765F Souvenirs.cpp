#include <algorithm>
#include <cstdio>
#include <cstring>
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
int n, m, a[N];
int tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void update(int rt, int l, int r, int pos, int val)
{
    tree[rt] = val;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    return max(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
int p[N], tot;
struct node
{
    int l, r, v;
    node(int _l = 0, int _r = 0, int _v = 0) : l(_l), r(_r), v(_v) {}
    inline bool operator<(const node &rhs) const
    {
        return l > rhs.l;
    }
} b[N * 30], q[N * 3];
int cnt;
int pre[N];
inline void update(int pos, int val)
{
    for (int i = pos; i <= n; i += lowbit(i))
        ckmin(pre[i], val);
}
inline int query(int pos)
{
    int res = 0x7fffffff;
    for (int i = pos; i; i -= lowbit(i))
        ckmin(res, pre[i]);
    return res;
}
int answer[N * 3];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[i] = a[i];
    }
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
    {
        int c = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
        int pos = 0;
        int minn = 1;
        while ((pos = query(1, 1, tot, minn, c)) > 0)
        {
            b[++cnt] = node(pos, i, a[i] - a[pos]);
            minn = (int)(upper_bound(p + 1, p + 1 + tot, (a[pos] + a[i]) / 2) - p);
        }
        int maxx = n;
        while ((pos = query(1, 1, tot, c + 1, maxx)) > 0)
        {
            b[++cnt] = node(pos, i, a[pos] - a[i]);
            maxx = (int)(upper_bound(p + 1, p + 1 + tot, (a[pos] + a[i]) / 2) - p - 1);
        }
        update(1, 1, tot, c, i);
    }
    sort(b + 1, b + 1 + cnt);
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r);
        q[i].v = i;
    }
    sort(q + 1, q + 1 + m);
    memset(pre, 0x3f, sizeof(pre));
    for (int i = n, j = 1, k = 1; i >= 1; --i)
    {
        while (j <= cnt && b[j].l == i)
        {
            update(b[j].r, b[j].v);
            ++j;
        }
        while (k <= m && q[k].l == i)
        {
            answer[q[k].v] = query(q[k].r);
            ++k;
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}