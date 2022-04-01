#include <algorithm>
#include <cstdio>
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
constexpr int N = 2e5 + 5;
constexpr int M = N * 100;
int n, m, type;
char str[N];
struct Point
{
    int ch[2];
    int fa, len;
} point[N];
int las = 1, tot = 1;
inline int insert(int c)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[p].len + 1 == point[q].len)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
    return np;
}
int where[N];
struct chairman_tree
{
    struct Tree
    {
        int l, r;
        int max;
    } tree[M];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
    int root[N], cnt;
    inline void pushup(int rt)
    {
        tree[rt].max = max(tree[lc(rt)].max, tree[rc(rt)].max);
    }
    inline void update(int &rt, int l, int r, int pos, int val)
    {
        ++cnt;
        tree[cnt] = tree[rt];
        rt = cnt;
        if (l == r)
        {
            ckmax(tree[rt].max, val);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc(rt), l, mid, pos, val);
        else
            update(rc(rt), mid + 1, r, pos, val);
        pushup(rt);
    }
    inline int query(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].max;
        int mid = (l + r) >> 1;
        return max(query(lc(rt), l, mid, x, y), query(rc(rt), mid + 1, r, x, y));
    }
#undef lc
#undef rc
} seg;
struct Tree
{
    int ch[2], fa;
    int color;
    int val, max;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
inline bool check(int x)
{
    return rc(fa(x)) == x;
}
inline bool nroot(int x)
{
    return lc(fa(x)) == x || rc(fa(x)) == x;
}
inline void pushup(int x)
{
    tree[x].max = max(tree[x].val, max(tree[lc(x)].max, tree[rc(x)].max));
}
inline void pushdown(int x)
{
    if (lc(x))
        tree[lc(x)].color = tree[x].color;
    if (rc(x))
        tree[rc(x)].color = tree[x].color;
}
inline void rotate(int x)
{
    int y = fa(x), z = fa(y), k = check(x), w = tree[x].ch[k ^ 1];

    if (nroot(y))
        tree[z].ch[check(y)] = x;
    fa(x) = z;

    tree[x].ch[k ^ 1] = y;
    fa(y) = x;

    tree[y].ch[k] = w;
    if (w)
        fa(w) = y;

    pushup(y), pushup(x);
}
int st[N];
inline void splay(int x)
{
    int top;
    st[top = 1] = x;
    for (int y = x; nroot(y); y = fa(y))
        st[++top] = fa(y);
    while (top)
        pushdown(st[top--]);
    while (nroot(x))
    {
        if (nroot(fa(x)))
            rotate(check(x) == check(fa(x)) ? fa(x) : x);
        rotate(x);
    }
}
inline void access(int x, int color)
{
    for (int y = 0; x; x = fa(y = x))
    {
        splay(x);
        rc(x) = 0;
        pushup(x);
        if (tree[x].color)
            seg.update(seg.root[color], 1, n, tree[x].color, tree[x].max);
        rc(x) = y;
        pushup(x);
    }
}
inline void solve(int x, int color)
{
    access(x, color);
    splay(x);
    tree[x].color = color;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("dance.in", "r", stdin);
    freopen("dance.out", "w", stdout);
#endif
    read(n, m, type);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
        where[i] = insert(str[i] - '0');
    for (int i = 1; i <= tot; ++i)
    {
        tree[i].max = tree[i].val = point[i].len;
        tree[i].fa = point[i].fa;
    }
    for (int i = 1; i <= n; ++i)
    {
        seg.root[i] = seg.root[i - 1];
        solve(where[i], i);
    }
    if (type)
    {
        int lastans = 0;
        while (m--)
        {
            int l, r;
            read(l, r);
            l ^= lastans, r ^= lastans;
            printf("%d\n", lastans = seg.query(seg.root[r], 1, n, l, r));
        }
    }
    else
        while (m--)
        {
            int l, r;
            read(l, r);
            printf("%d\n", seg.query(seg.root[r], 1, n, l, r));
        }
    return 0;
}
