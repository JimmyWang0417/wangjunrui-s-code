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
const int N = 3e4 + 1e5 + 5;
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
struct Tree
{
    int ch[2], fa;
    int size;
    bool rev;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
inline bool nroot(int x)
{
    return lc(find(fa(x))) == x || rc(find(fa(x))) == x;
}
inline bool check(int x)
{
    return rc(find(fa(x))) == x;
}
inline void reverse(int x)
{
    tree[x].rev ^= 1;
    swap(lc(x), rc(x));
}
inline void pushup(int x)
{
    tree[x].size = tree[lc(x)].size + tree[rc(x)].size + 1;
}
inline void pushdown(int x)
{
    if (tree[x].rev)
    {
        if (lc(x))
            reverse(lc(x));
        if (rc(x))
            reverse(rc(x));
        tree[x].rev = false;
    }
}
inline void rotate(int x)
{
    int y = find(fa(x)), z = find(fa(y)), k = check(x), w = tree[x].ch[k ^ 1];

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
    for (int y = x; nroot(y); y = find(fa(y)))
        st[++top] = find(fa(y));
    while (top)
        pushdown(st[top--]);
    while (nroot(x))
    {
        int y = find(fa(x));
        if (nroot(y))
            rotate(check(y) == check(x) ? y : x);
        rotate(x);
    }
}
inline void access(int x)
{
    x = find(x);
    for (int y = 0; x; x = find(fa(y = x)))
    {
        splay(x);
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
    reverse(x);
}
inline void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
int size[N];
inline void dfs(int x, int goal)
{
    fa[x] = goal;
    if (lc(x))
        dfs(lc(x), goal);
    if (rc(x))
        dfs(rc(x), goal);
}
inline void link(int x, int y)
{
    makeroot(x);
    fa(x) = y;
}
int n, m, q;
map<pair<int, int>, bool> mp;
struct node
{
    int opt, u, v;
} a[N];
inline void dfs(int u)
{
    if (lc(u))
        dfs(lc(u));
    printf(" %d", u);
    if (rc(u))
        dfs(rc(u));
}
inline void print(int u)
{
    dfs(u);
    putchar('\n');
}
int father[N];
inline int getfather(int x)
{
    return !father[x] ? x : father[x] = getfather(father[x]);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        if (u > v)
            swap(u, v);
        mp[make_pair(u, v)] = true;
    }
    for (int i = 1; i <= n; ++i)
        pushup(i);
    for (q = 1;; ++q)
    {
        int &opt = a[q].opt, &u = a[q].u, &v = a[q].v;
        read(opt);
        if (opt == -1)
            break;
        read(u, v);
        if (u > v)
            swap(u, v);
        if (!opt)
            mp[make_pair(u, v)] = false;
    }
    for (auto i : mp)
        if (i.second)
        {
            int x = find(i.first.first), y = find(i.first.second);
            if (x == y)
                continue;
            if (getfather(x) == getfather(y))
            {
                split(x, y);
                dfs(lc(y), y);
            }
            else
            {
                link(x, y);
                father[getfather(x)] = getfather(y);
            }
        }
    stack<int> s;
    for (int i = q - 1; i >= 1; --i)
    {
        int x = find(a[i].u), y = find(a[i].v);
        if (a[i].opt)
        {
            split(x, y);
            s.push(tree[y].size - 1);
        }
        else
        {
            if (x == y)
                continue;
            if (getfather(x) == getfather(y))
            {
                split(x, y);
                dfs(lc(y), y);
            }
            else
            {
                link(x, y);
                father[getfather(x)] = getfather(y);
            }
        }
    }
    while (!s.empty())
    {
        printf("%d\n", s.top());
        s.pop();
    }
    return 0;
}