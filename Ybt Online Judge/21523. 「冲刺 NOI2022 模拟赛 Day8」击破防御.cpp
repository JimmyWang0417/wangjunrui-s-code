#include <algorithm>
#include <climits>
#include <cstdio>
#include <list>
#include <random>
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
constexpr int mod = 998244353;
int n, m, T;
struct Tree
{
    int ch[2], fa;
    int id;
    int ans, val, key;
    int tag;
    int min;
    int size;
    inline void update(int _val)
    {
        tag += _val;
        ans += _val;
        min += _val;
    }
} tree[N * 2];
#define lc(rt) tree[rt].ch[0]
#define rc(rt) tree[rt].ch[1]
#define fa(rt) tree[rt].fa
mt19937 rnd(233);
int root[N * 4][2], cnt;
int where[N][2];
inline int newnode(int val, int ans, int id)
{
    int now = ++cnt;
    tree[now].val = val;
    tree[now].min = tree[now].ans = ans;
    tree[now].key = rnd();
    tree[now].size = 1;
    tree[now].tag = 0;
    tree[now].id = id;
    fa(now) = lc(now) = rc(now) = 0;
    return now;
}
inline void pushup(int now)
{
    tree[now].min = tree[now].ans;
    tree[now].size = 1;
    if (lc(now))
    {
        fa(lc(now)) = now;
        ckmin(tree[now].min, tree[lc(now)].min);
        tree[now].size += tree[lc(now)].size;
    }
    if (rc(now))
    {
        fa(rc(now)) = now;
        ckmin(tree[now].min, tree[rc(now)].min);
        tree[now].size += tree[rc(now)].size;
    }
}
inline void pushdown(int now)
{
    if (tree[now].tag)
    {
        if (lc(now))
            tree[lc(now)].update(tree[now].tag);
        if (rc(now))
            tree[rc(now)].update(tree[now].tag);
        tree[now].tag = 0;
    }
}
inline void split(int now, int val, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        fa(now) = 0;
        pushdown(now);
        if (tree[now].val <= val)
        {
            x = now;
            split(rc(now), val, rc(x), y);
            pushup(x);
        }
        else
        {
            y = now;
            split(lc(now), val, x, lc(y));
            pushup(y);
        }
    }
}
inline void splitsize(int now, int size, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        fa(now) = 0;
        pushdown(now);
        if (tree[lc(now)].size < size)
        {
            x = now;
            splitsize(rc(now), size - tree[lc(now)].size - 1, rc(x), y);
            pushup(x);
        }
        else
        {
            y = now;
            splitsize(lc(now), size, x, lc(y));
            pushup(y);
        }
    }
}
inline int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    else
    {
        if (tree[x].key > tree[y].key)
        {
            pushdown(x);
            rc(x) = merge(rc(x), y);
            pushup(x);
            return x;
        }
        else
        {
            pushdown(y);
            lc(y) = merge(x, lc(y));
            pushup(y);
            return y;
        }
    }
}
inline void solve(int rt, int l, int r, int x, int y, int w, int id)
{
    if (l == r)
    {
        root[rt][0] = merge(root[rt][0], where[id][0] = newnode(l, w, id));
        return;
    }
    int mid = (l + r) >> 1;
    if (y <= mid)
        solve(rt << 1, l, mid, x, y, w, id);
    else if (mid < x)
        solve(rt << 1 | 1, mid + 1, r, x, y, w, id);
    else
    {
        int a, b;
        split(root[rt][0], x, a, b);
        root[rt][0] = merge(merge(a, where[id][0] = newnode(x, w / 2, id)), b);
        split(root[rt][1], y, a, b);
        root[rt][1] = merge(merge(a, where[id][1] = newnode(y, (w + 1) / 2, id)), b);
    }
}
bool opp;
int nmsl[N], cnm;
int answer[N], tot;
int st[N], top;
inline void work(int id)
{
    int rt = where[id][opp];
    top = 0;
    while (rt)
    {
        st[++top] = rt;
        rt = fa(rt);
    }
    for (int i = top; i >= 1; --i)
        pushdown(st[i]);
    if (tree[where[id][0]].ans + tree[where[id][1]].ans < 0)
    {
        nmsl[++cnm] = id;
        return;
    }
    int res = tree[where[id][0]].ans + tree[where[id][1]].ans;
    tree[where[id][0]].ans = res / 2;
    tree[where[id][1]].ans = (res + 1) / 2;
    for (int i = 1; i <= top; ++i)
        pushup(st[i]);
}
inline void dfs(int rt)
{
    if (!rt)
        return;
    dfs(lc(rt));
    printf(" %d", tree[rt].ans);
    dfs(rc(rt));
    pushup(rt);
}
inline void dfs1(int rt)
{
    if (!rt)
        return;
    if (tree[rt].min > 0)
        return;
    pushdown(rt);
    if (tree[rt].ans < 0)
        work(tree[rt].id);
    dfs1(lc(rt));
    dfs1(rc(rt));
    pushup(rt);
}
inline void dfs2(int rt)
{
    if (!rt)
        return;
    if (tree[rt].min > 0)
        return;
    if (tree[rt].ans < 0)
        nmsl[++cnm] = tree[rt].id;
    pushdown(rt);
    dfs2(lc(rt));
    dfs2(rc(rt));
    pushup(rt);
}
inline int query(int now)
{
    int ans = tree[lc(now)].size;
    while (fa(now))
    {
        if (rc(fa(now)) == now)
            ans += tree[lc(fa(now))].size + 1;
        now = fa(now);
    }
    return ans;
}
inline void solve(int rt, int l, int r, int pos, int val)
{
    int x, y, z;
    if (l == r)
    {
        tree[root[rt][0]].update(-val);
        dfs2(root[rt][0]);
        for (int i = 1; i <= cnm; ++i)
        {
            int u = nmsl[i];
            splitsize(root[rt][0], query(where[u][0]), x, y);
            splitsize(y, 1, y, z);
            root[rt][0] = merge(x, z);
            answer[++tot] = u;
        }
        cnm = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
    {
        solve(rt << 1, l, mid, pos, val);
        split(root[rt][0], pos, x, y);
        tree[x].update(-val);
        opp = true;
        dfs1(x);
        root[rt][0] = merge(x, y);
    }
    else
    {
        solve(rt << 1 | 1, mid + 1, r, pos, val);
        split(root[rt][1], pos - 1, x, y);
        tree[y].update(-val);
        opp = false;
        dfs1(y);
        root[rt][1] = merge(x, y);
    }
    for (int i = 1; i <= cnm; ++i)
    {
        int u = nmsl[i];
        splitsize(root[rt][0], query(where[u][0]), x, y);
        splitsize(y, 1, y, z);
        root[rt][0] = merge(x, z);
        splitsize(root[rt][1], query(where[u][1]), x, y);
        splitsize(y, 1, y, z);
        root[rt][1] = merge(x, z);
        answer[++tot] = u;
    }
    cnm = 0;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("crazy.in", "r", stdin);
    freopen("crazy.out", "w", stdout);
#endif
    read(m, n, T);
    int lzx = 0;
    if (T)
    {
        ll lastans = 0;
        for (int i = 1; i <= m; ++i)
        {
            int opt;
            read(opt);
            if (opt == 1)
            {
                int l, r, w;
                read(l, r, w);
                l = (lastans + l - 1) % n + 1;
                r = (lastans + r - 1) % n + 1;
                w = w ^ lastans % mod;
                if (l > r)
                    swap(l, r);
                solve(1, 1, n, l, r, w, ++lzx);
            }
            else
            {
                int p, w;
                read(p, w);
                p = (lastans + p - 1) % n + 1;
                w = w ^ lastans % mod;
                solve(1, 1, n, p, w);
                sort(answer + 1, answer + 1 + tot);
                printf("%d", tot);
                for (int j = 1; j <= tot; ++j)
                {
                    printf(" %d", answer[j]);
                    lastans += answer[j];
                }
                putchar('\n');
                tot = 0;
            }
        }
    }
    else
    {
        for (int i = 1; i <= m; ++i)
        {
            int opt;
            read(opt);
            if (opt == 1)
            {
                int l, r, w;
                read(l, r, w);
                if (l > r)
                    swap(l, r);
                solve(1, 1, n, l, r, w, ++lzx);
            }
            else
            {
                int p, w;
                read(p, w);
                solve(1, 1, n, p, w);
                sort(answer + 1, answer + 1 + tot);
                printf("%d", tot);
                for (int j = 1; j <= tot; ++j)
                    printf(" %d", answer[j]);
                putchar('\n');
                tot = 0;
            }
        }
    }
    return 0;
}
