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
const int N = 5e4 + 5;
int n;
int p[N], tot;
struct Tree_array
{
    int c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= tot; i += lowbit(i))
            ckmax(c[i], val);
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            ckmax(res, c[i]);
        return res;
    }
    inline void clear(int pos)
    {
        for (int i = pos; i <= tot && c[i]; i += lowbit(i))
            c[i] = 0;
    }
} tree;
struct node
{
    int a, b, c, d;
    int w, ans;
    inline bool operator>(const node &rhs) const
    {
        return a == rhs.a ? (b == rhs.b ? (c == rhs.c ? d < rhs.d : c < rhs.c) : b < rhs.b) : a < rhs.a;
    }
    inline bool operator<(const node &rhs) const
    {
        return b == rhs.b ? (c == rhs.c ? d < rhs.d : c < rhs.c) : b < rhs.b;
    }
    inline bool operator==(const node &rhs) const
    {
        return a == rhs.a && b == rhs.b && c == rhs.c && d == rhs.d;
    }
} a[N];
pair<node, bool> b[N], c[N];
inline void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    sort(b + l, b + mid + 1, [](const pair<node, bool> &lhs, const pair<node, bool> &rhs)
         { return lhs.first.c < rhs.first.c; });
    sort(b + mid + 1, b + r + 1, [](const pair<node, bool> &lhs, const pair<node, bool> &rhs)
         { return lhs.first.c < rhs.first.c; });
    for (int i = l, j = mid + 1; j <= r; ++j)
    {
        while (i <= mid && b[i].first.c <= b[j].first.c)
        {
            if (!b[i].second)
                tree.update(b[i].first.d, b[i].first.ans);
            ++i;
        }
        if (b[j].second)
            ckmax(b[j].first.ans, tree.query(b[j].first.d) + b[j].first.w);
    }
    for (int i = l; i <= mid; ++i)
        if (!b[i].second)
            tree.clear(b[i].first.d);
    sort(b + mid + 1, b + r + 1);
    solve(mid + 1, r);
}
int answer;
inline void cdq(int l, int r)
{
    if (l == r)
    {
        ckmax(answer, a[l].ans);
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid);
    for (int i = l; i <= mid; ++i)
        b[i] = make_pair(a[i], false);
    for (int i = mid + 1; i <= r; ++i)
        b[i] = make_pair(a[i], true);
    sort(b + l, b + r + 1);
    solve(l, r);
    sort(b + l, b + r + 1, [](const pair<node, bool> &lhs, const pair<node, bool> &rhs)
         { return lhs.first > rhs.first; });
    for (int i = mid + 1; i <= r; ++i)
        a[i].ans = b[i].first.ans;
    cdq(mid + 1, r);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].a, a[i].b, a[i].c, a[i].d);
        p[i] = a[i].d;
    }
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
        a[i].d = (int)(lower_bound(p + 1, p + 1 + tot, a[i].d) - p);
    sort(a + 1, a + 1 + n, greater<node>());
    int now = 1;
    a[now].w = 1;
    for (int i = 2; i <= n; ++i)
        if (a[now] == a[i])
            ++a[now].w;
        else
        {
            a[++now] = a[i];
            a[now].w = 1;
        }
    n = now;
    for (int i = 1; i <= n; ++i)
        a[i].ans = a[i].w;
    // for (int i = 1; i <= n; ++i)
    //     printf(" %d %d %d %d %lld\n", a[i].a, a[i].b, a[i].c, a[i].d, a[i].w);
    cdq(1, n);
    printf("%d\n", answer);
    return 0;
}