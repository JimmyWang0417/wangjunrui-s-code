#include <algorithm>
#include <cstdio>
#define re register
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
using std::swap;
const int N = 1e5 + 5;
int cnt, root, a[N];
struct Tree
{
    int val, size;
    int ch[2], fa;
    bool reverse;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define val(x) tree[x].val
inline bool check(int x)
{
    return rc(fa(x)) == x;
}
inline void pushup(int now)
{
    tree[now].size = tree[lc(now)].size + tree[rc(now)].size + 1;
}
inline void pushdown(int now)
{
    if (!tree[now].reverse)
        return;
    swap(lc(now), rc(now)); //区间翻转
    if (lc(now))            //标记下放
        tree[lc(now)].reverse ^= 1;
    if (rc(now))
        tree[rc(now)].reverse ^= 1;
    tree[now].reverse = false; //下放后清空当前标记
}
inline void rorate(int x)
{
    int y = fa(x), z = fa(y);
    pushdown(y), pushdown(x);
    int k = check(x), w = tree[x].ch[k ^ 1];
    tree[y].ch[k] = w, fa(w) = y;
    tree[z].ch[check(y)] = x, fa(x) = z;
    tree[x].ch[k ^ 1] = y, fa(y) = x;
    pushup(y), pushup(x);
}
inline void splay(int x, int tar = 0)
{
    while (fa(x) != tar)
    {
        int y = fa(x), z = fa(y);
        if (z != tar)
            check(x) == check(y) ? rorate(y) : rorate(x);
        rorate(x);
    }
    if (!tar)
        root = x;
}
inline int build(int fa, int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1, now = ++cnt;
    fa(now) = fa;
    val(now) = a[mid];
    tree[now].size = 1;
    lc(now) = build(now, l, mid - 1), rc(now) = build(now, mid + 1, r);
    pushup(now);
    return now;
}
inline int k_th(int rk) //通过sze数组查找序列第k个元素
{
    int now = root;
    while (1)
    {
        pushdown(now);
        if (rk <= tree[lc(now)].size)
            now = lc(now);
        else if (rk > tree[lc(now)].size + 1)
        {
            rk -= tree[lc(now)].size + 1;
            now = rc(now);
        }
        else
        {
            splay(now);
            return now;
        }
    }
}
inline void reverse(int l, int r)
{
    int pre = k_th(l), nxt = k_th(r + 2);
    splay(pre), splay(nxt, pre);
    int now = lc(nxt);
    tree[now].reverse ^= 1;
    splay(now);
}
int n, m;
inline void dfs(int now)
{
    if (!now)
        return;
    pushdown(now);
    dfs(lc(now));
    if (1 <= val(now) && val(now) <= n)
        printf("%d ", val(now));
    dfs(rc(now));
}
inline void print(int now)
{ //按照序列顺序输出
    dfs(now);
    putchar('\n');
}
const int INF = 0x3f3f3f3f;
int main()
{
    read(n), read(m);
    for (re int i = 1; i <= n; ++i)
        a[i] = i;
    a[0] = a[n + 1] = -INF;
    root = build(0, 0, n + 1);
    //	print(root);
    while (m--)
    {
        int l, r;
        read(l), read(r);
        reverse(l, r);
    }
    print(root);
    return 0;
}
