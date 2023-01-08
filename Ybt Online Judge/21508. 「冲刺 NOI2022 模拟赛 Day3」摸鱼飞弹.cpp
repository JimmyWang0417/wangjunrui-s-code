#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 5e4 + 5;
int n, a[N];
struct Tree
{
    int l, r;
    ull sum;
} tree[N * 40];
int root[N], cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
ull power[N];
inline void update(int pre, int &rt, int l, int r, int pos, int val)
{
    rt = ++cnt;
    tree[rt] = tree[pre];
    if (l == r)
    {
        tree[rt].sum = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc(pre), lc(rt), l, mid, pos, val);
    else
        update(rc(pre), rc(rt), mid + 1, r, pos, val);
    tree[rt].sum = tree[lc(rt)].sum + tree[rc(rt)].sum * power[mid + 1 - l];
}
inline ull query(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum * power[l - x];
    int mid = (l + r) >> 1;
    return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
}
inline int query(int rt, int l, int r, int pos)
{
    if (l == r)
        return (int)tree[rt].sum;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(lc(rt), l, mid, pos);
    else
        return query(rc(rt), mid + 1, r, pos);
}
inline int lcp(int x, int y)
{
    int l = 1, r = n - max(x, y) + 1, ans = 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (query(root[x], 1, n, x, x + mid - 1) == query(root[y], 1, n, y, y + mid - 1))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return ans;
}
inline void print(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return;
    if (l == r)
    {
        printf("%d ", (int)tree[rt].sum);
        return;
    }
    int mid = (l + r) >> 1;
    print(lc(rt), l, mid, x, y);
    print(rc(rt), mid + 1, r, x, y);
}
int mp[N];
int id[N];
vector<int> g[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("waterflow.in", "r", stdin);
    freopen("waterflow.out", "w", stdout);
#endif
    read(n);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        id[i] = i;
        g[a[i]].push_back(i);
        power[i] = power[i - 1] * 13331;
    }
    for (int i = n; i >= 1; --i)
    {
        if (mp[a[i]])
            update(root[i + 1], root[i], 1, n, mp[a[i]], mp[a[i]] - i);
        else
            root[i] = root[i + 1];
        mp[a[i]] = i;
    }
    auto comp = [](int x, int y)
    {
        int len = lcp(x, y);
        if (len == n - max(x, y) + 1)
            return x > y;
        int fi = *lower_bound(g[a[x + len]].begin(), g[a[x + len]].end(), x) - x;
        int se = *lower_bound(g[a[y + len]].begin(), g[a[y + len]].end(), y) - y;
        return fi < se;
    };
    stable_sort(id + 1, id + 1 + n, comp);
    ll answer = (ll)n * (n + 1) / 2;
    for (int i = 2; i <= n; ++i)
        answer -= lcp(id[i - 1], id[i]);
    printf("%lld\n", answer);
    return 0;
}
