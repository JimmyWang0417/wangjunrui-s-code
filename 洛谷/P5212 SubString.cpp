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
using namespace std;
const int N = 1.2e6 + 5;
struct Tree
{
    int ch[2], fa;
    int size, val, fakesize;
    bool rev;
} tree[N];
#define fa(x) tree[x].fa
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
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
    tree[x].size = tree[x].val + tree[x].fakesize + tree[lc(x)].size + tree[rc(x)].size;
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
        tree[x].fakesize += tree[rc(x)].size - tree[y].size;
        rc(x) = y;
        pushup(x);
    }
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
    makeroot(x);
    fa(x) = y;
}
inline void cut(int x, int y)
{
    split(x, y);
    lc(y) = fa(x) = 0;
}
struct Point
{
    int ch[26], fa;
    int len;
} point[N];
int tot = 1, las = 1;
inline void insert(int c)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    tree[np].size = tree[np].val = 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
    {
        point[np].fa = 1;
        link(1, np);
    }
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            cut(q, point[q].fa);
            point[np].fa = point[q].fa = nq;
            link(np, nq), link(q, nq),link(point[nq].fa,nq);
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
}
int n;
char str[N];
inline void decode_with_mask(int mask)
{
    int len = (int)strlen(str);
    for (int i = 0; i < len; ++i)
    {
        mask = (mask * 131 + i) % len;
        swap(str[i], str[mask]);
    }
}
signed main()
{
    read(n);
    scanf("%s", str);
    for (int i = 0; str[i]; ++i)
        insert(str[i] - 'A');
    int mask = 0;
    while (n--)
    {
        char opt[10];
        scanf("%s%s", opt, str);
        decode_with_mask(mask);
        if (opt[0] == 'A')
        {
            for (int i = 0; str[i]; ++i)
                insert(str[i] - 'A');
        }
        else
        {
            int u = 1;
            for (int i = 0; str[i]; ++i)
                u = point[u].ch[str[i] - 'A'];
            if (!u)
                printf("0\n");
            else
            {
                makeroot(1);
                access(u);
                int res = tree[u].fakesize + 1;
                mask ^= res;
                printf("%d\n", res);
            }
        }
    }
    return 0;
}