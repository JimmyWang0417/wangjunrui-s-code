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
const int N = 5e5 + 5;
int n, m, a[N];
struct Tree
{
    int min, id;
    inline Tree operator+(const Tree &rhs)
    {
        Tree ans;
        if (min < rhs.min)
        {
            ans.min = min;
            ans.id = id;
        }
        else
        {
            ans.min = rhs.min;
            ans.id = rhs.id;
        }
        return ans;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt] = tree[lc] + tree[rc];
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].min = INT_MAX;
        tree[rt].id = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[rt].min = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
inline Tree query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return tree[0];
    if (x <= l && r <= y)
        return tree[rt];
    int mid = (l + r) >> 1;
    return query(lc, l, mid, x, y) + query(rc, mid + 1, r, x, y);
}
int p[N], tot;
int L[N], R[N];
int mp[N];
list<pair<int, int>> q[N];
int answer[N];
signed main()
{
    tree[0].min = INT_MAX;
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
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
        L[i] = mp[a[i]];
        mp[a[i]] = i;
    }
    for (int i = 1; i <= tot; ++i)
        mp[i] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        R[i] = mp[a[i]];
        mp[a[i]] = i;
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x, y);
        q[y].emplace_back(x, i);
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        if (L[i])
            update(1, 1, n, L[i], INT_MAX);
        update(1, 1, n, i, L[i] + 1);
        for (auto u : q[i])
        {
            Tree res = query(1, 1, n, u.first, i);
            answer[u.second] = (res.min > u.first ? 0 : p[res.id]);
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}