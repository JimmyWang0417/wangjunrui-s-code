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
const int N = 2e5 + 5;
int n, m, Log[N];
class SAM
{
public:
    struct Tree
    {
        int l, r;
        int size;
    } tree[N * 50];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
    int cnt, root[N];
    int id[N];
    inline void update(int &rt, int l, int r, int pos)
    {
        ++cnt;
        tree[cnt] = tree[rt];
        rt = cnt;
        ++tree[rt].size;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc(rt), l, mid, pos);
        else
            update(rc(rt), mid + 1, r, pos);
    }
    inline int merge(int x, int y, int l, int r)
    {
        if (!x || !y)
            return x | y;
        int rt = ++cnt;
        tree[rt].size = tree[x].size + tree[y].size;
        if (l == r)
            return rt;
        int mid = (l + r) >> 1;
        lc(rt) = merge(lc(x), lc(y), l, mid);
        rc(rt) = merge(rc(x), rc(y), mid + 1, r);
        return rt;
    }
    inline int query(int rt, int l, int r, int x, int y)
    {
        if (!rt || r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].size;
        int mid = (l + r) >> 1;
        return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
    }
    struct Point
    {
        int ch[26];
        int fa, len;
    } point[N];
    int tot, las;
    inline int insert(int c, int idd)
    {
        int p = las, np = las = ++tot;
        point[np].len = point[p].len + 1;
        update(root[np], 1, n, idd);
        for (; p && !point[p].ch[c]; p = point[p].fa)
            point[p].ch[c] = np;
        if (!p)
            point[np].fa = 1;
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
                point[np].fa = point[q].fa = nq;
                for (; p && point[p].ch[c] == q; p = point[p].fa)
                    point[p].ch[c] = nq;
            }
        }
        return np;
    }
    int nmsl[N], a[N];
    int fa[N][25], dep[N];
    inline void init(char *str)
    {
        tot = las = 1;
        for (int i = 1; i <= n; ++i)
            id[i] = insert(str[i] - 'a', i);
        for (int i = 1; i <= tot; ++i)
            ++nmsl[point[i].len];
        for (int i = 1; i <= n; ++i)
            nmsl[i] += nmsl[i - 1];
        for (int i = tot; i >= 1; --i)
            a[nmsl[point[i].len]--] = i;
        for (int i = tot; i >= 2; --i)
        {
            int u = a[i];
            root[point[u].fa] = merge(root[point[u].fa], root[u], 1, n);
        }
        for (int i = 2; i <= tot; ++i)
        {
            int u = a[i];
            fa[u][0] = point[u].fa;
            dep[u] = dep[point[u].fa] + 1;
            for (int j = 0; j < Log[dep[u]]; ++j)
                fa[u][j + 1] = fa[fa[u][j]][j];
        }
    }
    inline int getroot(int u, int len)
    {
        for (int i = Log[dep[u]]; i >= 0; --i)
            if (point[fa[u][i]].len >= len)
                u = fa[u][i];
        return u;
    }
    inline bool check(int u, int len, int x, int y)
    {
        return query(root[getroot(id[u], len)], 1, n, x + len - 1, y);
    }
} tree;
char str[N];
signed main()
{
    read(n, m);
    scanf("%s", str + 1);
    reverse(str + 1, str + 1 + n);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
        Log[i] = Log[i >> 1] + 1;
    tree.init(str);
    while (m--)
    {
        int a, b, c, d;
        read(b, a, d, c);
        a = n - a + 1;
        b = n - b + 1;
        c = n - c + 1;
        d = n - d + 1;

        int l = 1, r = min(b - a + 1, d - c + 1), ans = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (tree.check(d, mid, a, b))
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}