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
const int N = 1e5 + 5;
struct Tree
{
    int ch[2];
    int fa;
    int sum, val;
    bool reverse;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define sum(x) tree[x].sum
#define val(x) tree[x].val
#define rev(x) tree[x].reverse
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
    tree[x].sum = tree[lc(x)].sum ^ tree[rc(x)].sum ^ tree[x].val;
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
    for (re int y = x; nroot(y); y = fa(y))
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
inline void access(int x)
{
    for (re int y = 0; x; x = fa(y = x))
    {
        splay(x);
        rc(x) = y;
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
    if (findroot(x) == findroot(y))
        return;
    makeroot(x);
    fa(x) = y;
}
inline void cut(int x, int y)
{
    split(x, y);
    if (findroot(y) != x || fa(y) != x || lc(x))
        return;
    rc(x) = fa(y) = 0;
}
signed main()
{
    int n, m;
    read(n), read(m);
    for (re int i = 1; i <= n; ++i)
        read(tree[i].val);
    while (m--)
    {
        int opt, x, y;
        read(opt), read(x), read(y);
        if (opt == 0)
        {
            split(x, y);
            printf("%d\n", tree[y].sum);
        }
        else if (opt == 1)
            link(x, y);
        else if (opt == 2)
            cut(x, y);
        else if (opt == 3)
        {
            splay(x);
            tree[x].val = y;
            pushup(x);
        }
    }
    return 0;
}