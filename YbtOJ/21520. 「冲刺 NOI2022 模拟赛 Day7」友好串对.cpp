#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#define int ll
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
int n;
class segment_tree
{
public:
    struct Tree
    {
        int size;
        int sum;
        ll ans, kans;
        int tag;
        inline void update(int val)
        {
            tag += val;
            ans += (ll)size * val;
            kans = kans + (ll)sum * val;
        }
    } tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    inline void pushup(int rt)
    {
        tree[rt].ans = tree[lc].ans + tree[rc].ans;
        tree[rt].kans = tree[lc].kans + tree[rc].kans;
    }
    inline void pushdown(int rt)
    {
        if (tree[rt].tag)
        {
            tree[lc].update(tree[rt].tag);
            tree[rc].update(tree[rt].tag);
            tree[rt].tag = 0;
        }
    }
    inline void build(int rt, int l, int r)
    {
        if (l == r)
        {
            tree[rt].size = 1;
            tree[rt].sum = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        tree[rt].size = tree[lc].size + tree[rc].size;
        tree[rt].sum = tree[lc].sum + tree[rc].sum;
    }
    inline void update(int rt, int l, int r, int x, int y, int val)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(val);
        int mid = (l + r) >> 1;
        pushdown(rt);
        update(lc, l, mid, x, y, val);
        update(rc, mid + 1, r, x, y, val);
        pushup(rt);
    }
    inline int queryans(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].ans;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return queryans(lc, l, mid, x, y) + queryans(rc, mid + 1, r, x, y);
    }
    inline int querykans(int rt, int l, int r, int x, int y)
    {
        if (r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].kans;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return querykans(lc, l, mid, x, y) + querykans(rc, mid + 1, r, x, y);
    }
#undef lc
#undef rc
} seg;
class link_cut_tree
{
public:
    struct SAM
    {
        int ch[26];
        int fa, len;
    } point[N];
    inline int minlen(int x)
    {
        return point[point[x].fa].len + 1;
    }
    int las = 1, tot = 1;
    struct Tree
    {
        int ch[2], fa;
        int color;
        int min, max;
        bool rev;
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
    inline void pushup(int x)
    {
        tree[x].min = min(minlen(x), min(tree[lc(x)].min, tree[rc(x)].min));
        tree[x].max = max(point[x].len, max(tree[lc(x)].max, tree[rc(x)].max));
    }
    inline void pushdown(int x)
    {
        if (tree[x].rev)
        {
            swap(lc(x), rc(x));
            if (lc(x))
                tree[lc(x)].rev ^= 1;
            if (rc(x))
                tree[rc(x)].rev ^= 1;
        }
        if (lc(x))
            tree[lc(x)].color = tree[x].color;
        if (rc(x))
            tree[rc(x)].color = tree[x].color;
    }
    int st[N], top;
    inline void splay(int x)
    {
        st[top = 1] = x;
        for (int y = x; nroot(y); y = fa(y))
            st[++top] = fa(y);
        while (top)
            pushdown(st[top--]);
        while (nroot(x))
        {
            if (nroot(fa(x)))
                rotate(check(fa(x)) == check(x) ? fa(x) : x);
            rotate(x);
        }
    }
    inline void access(int x)
    {
        for (int y = 0; x; x = fa(y = x))
        {
            splay(x);
            rc(x) = 0;
            pushup(x);
            if (tree[x].color)
                seg.update(1, 1, n, tree[x].color - tree[x].max + 1, tree[x].color - tree[x].min + 1, -1);
            rc(x) = y;
            pushup(x);
        }
    }
    inline void cutdown(int x)
    {
        splay(x);
        rc(x) = 0;
    }
    inline void insert(int c, int id)
    {
        int p = las, np = las = ++tot;
        point[np].len = point[p].len + 1;
        pushup(np);
        for (; p && !point[p].ch[c]; p = point[p].fa)
            point[p].ch[c] = np;
        if (!p)
        {
            point[np].fa = 1;
            tree[np].fa = 1;
        }
        else
        {
            int q = point[p].ch[c];
            if (point[q].len == point[p].len + 1)
            {
                point[np].fa = q;
                tree[np].fa = q;
            }
            else
            {
                cutdown(point[q].fa);
                splay(q);
                int nq = ++tot;
                point[nq] = point[q];
                point[nq].len = point[p].len + 1;
                tree[nq].color = tree[q].color;
                tree[nq].fa = tree[q].fa;
                pushup(nq);
                point[np].fa = point[q].fa = nq;
                tree[np].fa = tree[q].fa = nq;
                for (; p && point[p].ch[c] == q; p = point[p].fa)
                    point[p].ch[c] = nq;
            }
        }
        access(np);
        splay(np);
        tree[np].color = id;
        seg.update(1, 1, n, id - tree[np].max + 1, id - tree[np].min + 1, 1);
    }
#undef lc
#undef rc
#undef fa
} tree;
char str[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("substr.in", "r", stdin);
    freopen("substr.out", "w", stdout);
#endif
    tree.tree[0].min = INT_MAX, tree.tree[0].max = INT_MIN;
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    seg.build(1, 1, n);
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        tree.insert(str[i] - 'a', i);
        int pos = i - tree.minlen(tree.las) + 1;
        ans += seg.querykans(1, 1, n, 1, pos) + (ll)pos * seg.queryans(1, 1, n, pos + 1, i);
    }
    ll sum = 0;
    for (int i = 2; i <= tree.tot; ++i)
        sum += tree.point[i].len - tree.point[tree.point[i].fa].len;
    printf("%lld\n", (sum & 1 ? (sum + 1) / 2 * sum : (sum / 2 * (sum + 1))) - ans);
    return 0;
}
