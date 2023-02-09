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
const int N = 1e5 + 5;
struct Tree
{
    int l, r;
    int size;
} tree[N * 40];
int root[N], cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void update(int pre, int &rt, int l, int r, int pos, int val)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    tree[rt].size += val;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos, val);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos, val);
}
inline int query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].size;
    int mid = (l + r) >> 1;
    return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
}
inline int query(int rt, int l, int r, int cnt)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (cnt <= tree[lc(rt)].size)
        return query(lc(rt), l, mid, cnt);
    else
        return query(rc(rt), mid + 1, r, cnt - tree[lc(rt)].size);
}
int n, a[N];
int mp[N];
list<int> g[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        g[mp[a[i]] + 1].push_back(i);
        mp[a[i]] = i;
    }
    g[n].push_back(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        root[i] = root[i - 1];
        for (auto u : g[i])
            update(root[i], root[i], 1, n + 1, u, 1);
    }
    for (int k = 1; k <= n; ++k)
    {
        int tot = 0;
        for (int l = 1, r = 1; l <= n; l = r, ++tot)
            r = query(root[l], 1, n + 1, query(root[l], 1, n + 1, 1, l - 1) + k + 1);
        printf("%d ", tot);
    }
    return 0;
}