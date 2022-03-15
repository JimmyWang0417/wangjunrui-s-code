// Problem: E. Pastoral Oddities
// Contest: Codeforces - Codeforces Round #334 (Div. 1)
// URL: https://codeforces.com/problemset/problem/603/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
const int N = 4e5 + 5;
int n, m;
struct node
{
    int u, v, w;
} a[N];
struct Tree
{
    int ch[2], fa;
    int size, fakesize;
    int id, ans;
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
    tree[x].size = tree[lc(x)].size + tree[rc(x)].size + tree[x].fakesize + (x <= n);
    tree[x].ans = tree[x].id;
    if (a[tree[x].ans].w < a[tree[lc(x)].ans].w)
        tree[x].ans = tree[lc(x)].ans;
    if (a[tree[x].ans].w < a[tree[rc(x)].ans].w)
        tree[x].ans = tree[rc(x)].ans;
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
        tree[x].fakesize += tree[rc(x)].size - tree[y].size;
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
int answer;
inline void link(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);

    if (tree[x].size & 1)
        --answer;
    if (tree[y].size & 1)
        --answer;

    fa(x) = y;
    tree[y].fakesize += tree[x].size;
    pushup(y);

    if (tree[y].size & 1)
        ++answer;
}
inline void cut(int x, int y)
{
    split(x, y);

    if (tree[y].size & 1)
        --answer;
    fa(x) = lc(y) = 0;
    pushup(y);

    if (tree[x].size & 1)
        ++answer;
    if (tree[y].size & 1)
        ++answer;
}
__gnu_pbds::priority_queue<pair<int, int>> q;
__gnu_pbds::priority_queue<pair<int, int>>::point_iterator its[N];
signed main()
{
    read(n, m);
    a[0].w = -0x3f3f3f3f;
    for (int i = 1; i <= n; ++i)
        pushup(i);
    answer = n;
    for (int i = 1; i <= m; ++i)
    {
        int &u = a[i].u, &v = a[i].v, &w = a[i].w;
        read(a[i].u, a[i].v, a[i].w);
        tree[i + n].id = i;
        pushup(i + n);
        if (findroot(u) == findroot(v))
        {
            split(u, v);
            int o = tree[v].ans;
            if (a[o].w > w)
            {
                cut(a[o].u, o + n), cut(o + n, a[o].v);
                link(u, i + n), link(i + n, v);
                q.erase(its[o]);
                its[i] = q.push(make_pair(a[i].w, i));
            }
        }
        else
        {
            link(u, i + n), link(i + n, v);
            its[i] = q.push(make_pair(a[i].w, i));
        }
        if (answer)
        {
            printf("-1\n");
            continue;
        }
        while (!q.empty())
        {
            int o = q.top().second;
            q.pop();
            cut(a[o].u, o + n), cut(o + n, a[o].v);
            if (answer)
            {
                link(a[o].u, o + n), link(o + n, a[o].v);
                q.push(make_pair(a[o].w, o));
                break;
            }
        }
        printf("%d\n", q.top().first);
    }
    return 0;
}