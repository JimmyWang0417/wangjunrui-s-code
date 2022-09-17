#include <algorithm>
#include <cstdio>
#define ll long long
#define lll __int128
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
constexpr int N = 70000;
constexpr int block = 225;
int num;
struct node
{
    int a[block * 2 + 5], size;
    int next;
    struct Tree
    {
        int l, r;
        int size;
    } tree[block * 2 * 40 + 5];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
    int root, cnt;
    inline int newnode()
    {
        int rt = ++cnt;
        lc(rt) = rc(rt) = tree[rt].size = 0;
        return rt;
    }
    inline void add(int &rt, int l, int r, int pos)
    {
        if (!rt)
            rt = newnode();
        ++tree[rt].size;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            add(lc(rt), l, mid, pos);
        else
            add(rc(rt), mid + 1, r, pos);
    }
    inline void del(int &rt, int l, int r, int pos)
    {
        if (!rt)
            rt = newnode();
        --tree[rt].size;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            del(lc(rt), l, mid, pos);
        else
            del(rc(rt), mid + 1, r, pos);
    }
    inline void modify(int pos, int val)
    {
        del(root, 0, 7e4, a[pos]);
        add(root, 0, 7e4, a[pos] = val);
    }
    inline void insert(int pos, int val)
    {
        for (int i = size; i >= pos; --i)
            a[i + 1] = a[i];
        add(root, 0, 7e4, a[pos] = val);
        ++size;
    }
    inline void init()
    {
        for (int i = 1; i <= size; ++i)
            add(root, 0, 7e4, a[i]);
    }
    inline void clear()
    {
        root = size = cnt = 0;
    }
    inline void split(node *that)
    {
        for (int i = block + 1; i <= size; ++i)
            that->a[++that->size] = a[i];
        clear();
        size = block;
        init(), that->init();
    }
} a[N / block + 5];
int queryroot[N / block + 5], querywhere[N / block + 5], querycnt;
int p[block * 4 + 5], tot;
inline void insert(int pos, int val)
{
    int bl = 0;
    for (bl = 1; a[bl].next && pos > a[bl].size; pos -= a[bl].size, bl = a[bl].next)
        ;
    a[bl].insert(pos, val);
    if (a[bl].size >= 2 * block)
    {
        ++num;
        a[bl].split(&a[num]);
        a[num].next = a[bl].next;
        a[bl].next = num;
    }
}
inline void modify(int pos, int val)
{
    int bl = 0;
    for (bl = 1; a[bl].next && pos > a[bl].size; pos -= a[bl].size, bl = a[bl].next)
        ;
    a[bl].modify(pos, val);
}
inline int ask(int l, int r, int k_th)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    int cnt = (int)(upper_bound(p + 1, p + 1 + tot, mid) - lower_bound(p + 1, p + 1 + tot, l));
    for (int i = 1; i <= querycnt; ++i)
        cnt += a[querywhere[i]].tree[a[querywhere[i]].lc(queryroot[i])].size;
    if (k_th <= cnt)
    {
        for (int i = 1; i <= querycnt; ++i)
            queryroot[i] = a[querywhere[i]].lc(queryroot[i]);
        return ask(l, mid, k_th);
    }
    else
    {
        for (int i = 1; i <= querycnt; ++i)
            queryroot[i] = a[querywhere[i]].rc(queryroot[i]);
        return ask(mid + 1, r, k_th - cnt);
    }
}
inline int query(int l, int r, int k_th)
{
    int L = 0;
    for (L = 1; a[L].next && l > a[L].size; l -= a[L].size, L = a[L].next)
        ;
    int R = 0;
    for (R = 1; a[R].next && r > a[R].size; r -= a[R].size, R = a[R].next)
        ;
    if (L == R)
    {
        tot = 0;
        for (int i = l; i <= r; ++i)
            p[++tot] = a[L].a[i];
        sort(p + 1, p + 1 + tot);
        return p[k_th];
    }
    else
    {
        querycnt = tot = 0;
        for (int i = l; i <= a[L].size; ++i)
            p[++tot] = a[L].a[i];
        for (int i = 1; i <= r; ++i)
            p[++tot] = a[R].a[i];
        sort(p + 1, p + 1 + tot);
        if (a[L].next == R)
            return p[k_th];
        else
        {
            for (int i = a[L].next; i != R; i = a[i].next)
            {
                ++querycnt;
                queryroot[querycnt] = a[i].root;
                querywhere[querycnt] = i;
            }
            return ask(0, 7e4, k_th);
        }
    }
}
signed main()
{
    int n, m;
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        if ((i - 1) % block == 0)
            ++num;
        read(a[num].a[++a[num].size]);
    }
    for (int i = 1; i < num; ++i)
        a[i].next = i + 1;
    for (int i = 1; i <= num; ++i)
        a[i].init();
    read(m);
    int lastans = 0;
    for (int i = 1; i <= m; ++i)
    {
        static char str[4];
        scanf("%s", str);
        if (str[0] == 'Q')
        {
            int l, r, k_th;
            read(l, r, k_th);
            l ^= lastans, r ^= lastans, k_th ^= lastans;
            printf("%d\n", lastans = query(l, r, k_th));
        }
        else if (str[0] == 'M')
        {
            int pos, val;
            read(pos, val);
            pos ^= lastans, val ^= lastans;
            modify(pos, val);
        }
        else
        {
            int pos, val;
            read(pos, val);
            pos ^= lastans, val ^= lastans;
            insert(pos, val);
        }
    }
    return 0;
}