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
int n, m;
struct node
{
    int c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
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
        for (int i = pos; i<=n && c[i]; i += lowbit(i))
            c[i] = 0;
    }
} tree;
struct Query
{
    int val, l, r, id, ans;
} a[N];
inline bool cmp1(const Query &lhs, const Query &rhs)
{
    return lhs.val < rhs.val;
}
inline bool cmp2(const Query &lhs, const Query &rhs)
{
    return lhs.l < rhs.l;
}
inline bool cmp3(const Query &lhs, const Query &rhs)
{
    return lhs.id < rhs.id;
}
int answer = 0;
inline void cdq(int l, int r)
{
    if (l == r)
    {
        ckmax(a[l].ans, 1);
        ckmax(answer, a[l].ans);
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid);
    sort(a + l, a + mid + 1, cmp1);
    sort(a + mid + 1, a + r + 1, cmp2);
    for (int i = l, j = mid + 1; j <= r; ++j)
    {
        while (i <= mid && a[i].val <= a[j].l)
        {
            tree.update(a[i].r, a[i].ans);
            ++i;
        }
        ckmax(a[j].ans, tree.query(a[j].val) + 1);
    }
    for (int i = l; i <= mid; ++i)
        tree.clear(a[i].r);
    sort(a + mid + 1, a + r + 1, cmp3);
    cdq(mid + 1, r);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].val);
        a[i].l = a[i].r = a[i].val;
        a[i].id = i;
    }
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        ckmin(a[x].l, y);
        ckmax(a[x].r, y);
    }
    cdq(1, n);
    printf("%d\n", answer);
    return 0;
}