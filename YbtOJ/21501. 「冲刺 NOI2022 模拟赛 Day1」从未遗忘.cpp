#include <cmath>
#include <cstdio>
#include <algorithm>
#define ll long long
#define ull unsigned long long
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
constexpr ull mod = 9606826076640600000ull;
constexpr long double eps = 1e-12;
inline ull trans(ull x)
{
    long double y = pow(x, 0.3333333333);
    ull z = (ull)y;
    if (y - z - 0.2 < -eps)
        return z;
    if (y - z - 0.3 < -eps)
        return z + 1;
    if (y - z - 0.6 < -eps)
        return z;
    return z + 1;
}
inline ull lzxcnm(ull x, ull y)
{
    return (ull)(((__int128)x + (__int128)y) % mod);
}
inline ull lzxnmsl(ull x, ull y)
{
    return (ull)((((__int128)x - (__int128)y) % mod + (__int128)mod) % mod);
}
int n, m;
ull a[N];
struct Tree
{
    int ch[2];
    int fa;
    ull val, sum, fakesum, max, all;
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
inline void pushup(int x)
{
    tree[x].max = max(tree[x].val, max(tree[lc(x)].max, tree[rc(x)].max));
    tree[x].sum = lzxcnm(tree[x].val, lzxcnm(tree[lc(x)].sum, tree[rc(x)].sum));
    tree[x].all = lzxcnm(lzxcnm(tree[x].fakesum, tree[x].val), lzxcnm(tree[lc(x)].all, tree[rc(x)].all));
}
inline void pushdown(int x)
{
    if (tree[x].rev)
    {
        if (lc(x))
            tree[lc(x)].rev ^= 1;
        if (rc(x))
            tree[rc(x)].rev ^= 1;
        swap(lc(x), rc(x));
        tree[x].rev = false;
    }
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
            rotate(check(fa(x)) == check(x) ? fa(x) : x);
        rotate(x);
    }
}
inline void access(int x)
{
    for (int y = 0; x; x = fa(y = x))
    {
        splay(x);
        tree[x].fakesum = lzxcnm(tree[x].fakesum, tree[rc(x)].all);
        tree[x].fakesum = lzxnmsl(tree[x].fakesum, tree[y].all);
        rc(x) = y;
        pushup(x);
    }
}
inline int findroot(int x)
{
    access(x);
    splay(x);
    while (pushdown(x), lc(x))
        x = lc(x);
    splay(x);
    return x;
}
inline void makeroot(int x)
{
    access(x);
    splay(x);
    tree[x].rev ^= 1;
}
inline void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
inline void link(int x, int y)
{
    if (findroot(x) == findroot(y))
        return;
    makeroot(x), makeroot(y);
    fa(x) = y;
    tree[y].fakesum = lzxcnm(tree[y].fakesum, tree[x].all);
    pushup(y);
}
inline void cut(int x, int y)
{
    if (findroot(x) != findroot(y))
        return;
    split(x, y);
    fa(x) = lc(y) = 0;
    pushup(y);
}
inline void dfs(int u)
{
    if (!u || tree[u].max <= 2)
        return;
    dfs(lc(u));
    dfs(rc(u));
    tree[u].val = trans(tree[u].val);
    pushup(u);
}
inline ull calc(int u)
{
    makeroot(u);
    access(u);
    return lzxcnm(tree[u].fakesum, tree[u].val);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("unforgettable.in", "r", stdin);
    freopen("unforgettable.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        tree[i].val = a[i];
        pushup(i);
    }
    read(m);
    for (int i = 1; i <= m; ++i)
    {
        int opt1, opt2;
        read(opt1, opt2);
        if (opt1 == 1)
        {
            if (opt2 == 1)
            {
                int x, y;
                read(x, y);
                if (findroot(x) == findroot(y))
                {
                    split(x, y);
                    dfs(y);
                }
            }
            else if (opt2 == 2)
            {
                int x, y;
                read(x, y);
                cut(x, y);
            }
            else
            {
                int x, y;
                read(x, y);
                link(x, y);
            }
        }
        else
        {
            if (opt2 == 1)
            {
                int x, y;
                read(x, y);
                if (findroot(x) == findroot(y))
                {
                    split(x, y);
                    printf("%llu\n", tree[y].sum);
                }
                else
                    printf("%llu\n", lzxcnm(calc(x), calc(y)));
            }
            else
            {
                int x;
                read(x);
                printf("%llu\n", calc(x));
            }
        }
    }
    return 0;
}
