#include <climits>
#include <cstdio>
#include <random>
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
constexpr int N = 1e5 + 5;
mt19937 rnd(233);
int n;
struct Tree
{
    int ch[2];
    int size;
    int key;
    ll val, end;
    ll k, b;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
int root, cnt;
inline void update(int now, ll _k, ll _b)
{
    tree[now].k += _k, tree[now].b += _b;
    tree[now].val += _b + _k * (tree[lc(now)].size + 1);
    tree[now].end += _b + _k * tree[now].size;
}
inline int newnode(ll val)
{
    int now = ++cnt;
    tree[now].val = tree[now].end = val;
    tree[now].size = 1;
    tree[now].key = (int)rnd();
    return now;
}
inline void pushup(int now)
{
    tree[now].size = tree[lc(now)].size + tree[rc(now)].size + 1;
    tree[now].end = rc(now) ? tree[rc(now)].end : tree[now].val;
}
inline void pushdown(int now)
{
    if (tree[now].k || tree[now].b)
    {
        if (lc(now))
            update(lc(now), tree[now].k, tree[now].b);
        if (rc(now))
            update(rc(now), tree[now].k, tree[now].b + (tree[lc(now)].size + 1) * tree[now].k);
        tree[now].k = tree[now].b = 0;
    }
}
inline void split(int now, int size, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        pushdown(now);
        if (tree[lc(now)].size < size)
        {
            x = now;
            split(rc(now), size - tree[lc(now)].size - 1, rc(x), y);
        }
        else
        {
            y = now;
            split(lc(now), size, x, lc(y));
        }
        pushup(now);
    }
}
inline int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    else
    {
        if (tree[x].key > tree[y].key)
        {
            pushdown(x);
            rc(x) = merge(rc(x), y);
            pushup(x);
            return x;
        }
        else
        {
            pushdown(y);
            lc(y) = merge(x, lc(y));
            pushup(y);
            return y;
        }
    }
}
inline int query(int val)
{
    int size = 0, now = root;
    ll las = 0;
    while (now)
    {
        pushdown(now);
        ll lower = lc(now) ? tree[lc(now)].end : las;
        if (lower + (ll)(tree[lc(now)].size + size + 1) * val > tree[now].val)
            now = lc(now);
        else
        {
            las = tree[now].val;
            size += tree[lc(now)].size + 1;
            now = rc(now);
        }
    }
    return size;
}
inline void print(int u)
{
    if (!u)
        return;
    pushdown(u);
    print(lc(u));
    printf("%lld ", tree[u].val);
    print(rc(u));
}
inline ll dfs(int u)
{
    if (!u)
        return 0;
    pushdown(u);
    return max(tree[u].val, max(dfs(lc(u)), dfs(rc(u))));
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int val;
        read(val);
        int x, y;
        int size = query(val);
        split(root, size, x, y);
        y = merge(newnode(tree[x].end), y);
        update(y, val, (ll)tree[x].size * val);
        root = merge(x, y);
    }
    printf("%lld\n", dfs(root));
    return 0;
}