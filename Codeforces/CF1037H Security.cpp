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
class SAM
{
public:
    int n;
    struct Tree
    {
        int l, r;
        int size;
    } tree[N * 50];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
    int cnt, root[N];
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
    inline void insert(int c, int id)
    {
        int p = las, np = las = ++tot;
        point[np].len = point[p].len + 1;
        update(root[np], 1, n, id);
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
    }
    int nmsl[N], a[N];
    inline void work(char *str)
    {
        tot = las = 1;
        n = (int)strlen(str + 1);
        for (int i = 1; i <= n; ++i)
            insert(str[i] - 'a', i);
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
    }
    char answer[N];
    int m;
    inline void query(char *str, int l, int r)
    {
        a[m = 0] = 1;
        for (int i = 0, u = 1; str[i]; ++i)
        {
            int c = str[i] - 'a';
            if (point[u].ch[c] && query(root[point[u].ch[c]], 1, n, l + i, r))
                a[++m] = u = point[u].ch[c];
            else
                break;
        }
        // for (int i = 0; i <= m; ++i)
        //     printf("%d ", a[i]);
        // putchar('\n');
        for (int i = m; i >= 0; --i)
        {
            int u = a[i];
            for (int j = max(str[i] - 'a' + 1, 0); j < 26; ++j)
            {
                if (point[u].ch[j] && query(root[point[u].ch[j]], 1, n, l + i, r))
                {
                    for (int k = 0; k < i; ++k)
                        putchar(str[k]);
                    putchar(j + 'a');
                    putchar('\n');
                    return;
                }
            }
        }
        printf("-1\n");
    }
} tree;
char str[N];
signed main()
{
    scanf("%s", str + 1);
    tree.work(str);
    int T;
    read(T);
    while (T--)
    {
        int l, r;
        read(l, r);
        scanf("%s", str);
        tree.query(str, l, r);
    }
    return 0;
}