#include <algorithm>
#include <cstdio>
#define re register
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
const int N = 2e5 + 5;
struct Tree
{
    int ch[2];
    int fa;
    int size;
    bool reverse;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define size(x) tree[x].size
#define rev(x) tree[x].reverse
inline bool check(int x)
{
    return rc(fa(x)) == x;
}
inline void pushup(int x)
{
    size(x) = size(lc(x)) + size(rc(x)) + 1;
}
inline void pushdown(int x)
{
    if (!rev(x))
        return;
    swap(lc(x), rc(x));
    if (lc(x))
        rev(lc(x)) ^= 1;
    if (rc(x))
        rev(rc(x)) ^= 1;
    rev(x) = false;
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
    tree[y].ch[k] = w;
    tree[x].ch[k ^ 1] = y;
    if (w)
        fa(w) = y;
    fa(y) = x;
    fa(x) = z;
    pushup(y), pushup(x);
}
int st[N];
inline void splay(int x)
{
    int top;
    st[top = 1] = x;
    for (re int i = x; nroot(i); i = fa(i))
        st[++top] = fa(i);
    while (top)
        pushdown(st[top--]);
    while (nroot(x))
    {
        if (nroot(fa(x)))
            check(x) == check(fa(x)) ? rotate(fa(x)) : rotate(x);
        rotate(x);
    }
}
inline void access(int x)
{
    for (re int y = 0; x; y = x, x = fa(y))
    {
        splay(x);
        rc(x) = y;
        if (y)
            fa(y) = x;
        pushup(x);
    }
}
inline void makeroot(int x)
{
    access(x);
    splay(x);
    rev(x) ^= 1;
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
inline void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
inline void link(int x, int y)
{
    makeroot(x);
    fa(x) = y;
}
inline void cut(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
    lc(y) = fa(x) = 0;
    pushup(x);
}
inline int query(int x, int k)
{
    while (1)
    {
        pushdown(x);
        if (k == tree[lc(x)].size + 1)
            return x;
        if (k <= tree[lc(x)].size)
            x = lc(x);
        else
        {
            k -= tree[lc(x)].size + 1;
            x = rc(x);
        }
    }
}
inline void dfs(int x)
{
    pushdown(x);
    if (lc(x))
        dfs(lc(x));
    printf("%d ", x);
    if (rc(x))
        dfs(rc(x));
}
inline void print(int x)
{
    dfs(x);
    putchar('\n');
}
int p[N];
signed main()
{
    int n, m;
    read(n, m);
    for (re int i = 1; i <= n; ++i)
    {
        read(p[i]);
        link(i, min(i + p[i], n + 1));
    }
    while (m--)
    {
        int opt, pos;
        read(opt, pos);
        if (opt == 1)
        {
            split(n + 1, pos);
            printf("%d %d\n", query(pos, 2), tree[pos].size - 1);
        }
        else
        {
            int val;
            read(val);
            cut(pos, min(pos + p[pos], n + 1));
            link(pos, min(pos + (p[pos] = val), n + 1));
        }
    }
    return 0;
}