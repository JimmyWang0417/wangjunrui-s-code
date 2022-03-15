#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e5 + 5;
struct node
{
    int l, r, v;
    inline bool operator<(const node &rhs) const
    {
        return l < rhs.l;
    }
} a[N];
int w, n;
int p[N], tot;
struct Tree_array
{
    int c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= tot; i += lowbit(i))
            c[i] = max(c[i], val);
    }
    inline int query(int pos)
    {
        int res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res = max(res, c[i]);
        return res;
    }
} tree;
signed main()
{
    read(w, n);
    for (int i = 1; i <= n; ++i)
    {
        int t, pos;
        read(t, pos, a[i].v);
        a[i].l = 2 * t - pos, p[i] = a[i].r = 2 * t + pos;
    }
    sort(a + 1, a + 1 + n);
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
    {
        int c = (int)(lower_bound(p + 1, p + 1 + tot, a[i].r) - p);
        int res = tree.query(c) + a[i].v;
        tree.update(c, res);
    }
    printf("%d\n", tree.query(tot));
    return 0;
}
