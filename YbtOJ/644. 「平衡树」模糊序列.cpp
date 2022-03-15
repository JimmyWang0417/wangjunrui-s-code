#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 3e5 + 5;
int n;
random_device rd;
mt19937 rnd(rd());
struct Tree
{
    int l, r;
    int val;
    int ans, max, tag;
    long unsigned int key;
    inline void update(int _val)
    {
        tag += _val;
        max += _val;
        ans += _val;
        val += _val;
    }
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt, root;
inline int newnode(int val, int ans)
{
    int x = ++cnt;
    tree[x].val = val;
    tree[x].max = tree[x].ans = ans;
    tree[x].key = rnd();
    return x;
}
inline void pushup(int x)
{
    tree[x].max = max(tree[x].ans, max(tree[lc(x)].max, tree[rc(x)].max));
}
inline void pushdown(int x)
{
    if (tree[x].tag)
    {
        if (lc(x))
            tree[lc(x)].update(tree[x].tag);
        if (rc(x))
            tree[rc(x)].update(tree[x].tag);
        tree[x].tag = 0;
    }
}
inline void split(int now, int val, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        pushdown(now);
        if (tree[now].val <= val)
        {
            x = now;
            split(rc(now), val, rc(x), y);
            pushup(x);
        }
        else
        {
            y = now;
            split(lc(now), val, x, lc(y));
            pushup(y);
        }
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
signed main()
{
    freopen("vague.in","r",stdin);
    freopen("vague.out","w",stdout);
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int l, r;
        read(l, r);
        int x, y, z, nmsl;
        split(root, r - 1, y, z);
        split(y, l - 1, x, y);
        split(z, r, nmsl, z);
        if (y)
            tree[y].update(1);
        int res = tree[x].max + 1;
        root = merge(merge(x, newnode(l, res)), merge(y, z));
    }
    printf("%d\n",tree[root].max);
    return 0;
}