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
int n;
struct node
{
    int l, r, v;
    node(int _l = 0, int _r = 0, int _v = 0) : l(_l), r(_r), v(_v) {}
    inline bool operator<(const node &rhs) const
    {
        return l == rhs.l ? r < rhs.r : l < rhs.l;
    }
    inline bool operator==(const node &rhs) const
    {
        return l == rhs.l && r == rhs.r;
    }
} a[N];
int tot;
struct Tree_array
{
    int sum[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            ckmax(sum[i], val);
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            ckmax(res, sum[i]);
        return res;
    }
} tree;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        read(x, y);
        int l = x + 1, r = n - y;
        if (l > r)
            continue;
        a[++tot] = node(l, r);
    }
    sort(a + 1, a + 1 + tot);
    int cnt = 0;
    for (int i = 1; i <= tot; ++i)
        if (a[i] == a[i - 1])
            ++a[cnt].v;
        else
        {
            a[++cnt] = a[i];
            a[cnt].v = 1;
        }
    for (int i = 1; i <= cnt; ++i)
        ckmin(a[i].v, a[i].r - a[i].l + 1);
    for (int i = 1; i <= cnt; ++i)
        tree.update(a[i].r, tree.query(a[i].l - 1) + a[i].v);
    printf("%d\n", n - tree.query(n));
    return 0;
}