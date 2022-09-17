#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 2e6 + 5;
int n, maxlen[N];
char S[N];
namespace SAM1
{
    struct Tree
    {
        int l, r, size;
    } tree[N * 40];
    int root[N], cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
    inline void pushup(int rt)
    {
        tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size;
    }
    inline void update(int &rt, int l, int r, int pos, int val)
    {
        if (!rt)
            rt = ++cnt;
        tree[rt].size += val;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc(rt), l, mid, pos, val);
        else
            update(rc(rt), mid + 1, r, pos, val);
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
        if (r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].size;
        int mid = (l + r) >> 1;
        return query(lc(rt), l, mid, x, y) + query(rc(rt), mid + 1, r, x, y);
    }
    struct SAM
    {
        int fa, len, ch[26];
    } point[N];
    int tot = 1, las = 1;
    inline void insert(int c, int id)
    {
        int p = las, np = las = ++tot;
        point[np].len = point[p].len + 1;
        update(root[np], 1, n, id, 1);
        for (; p && !point[p].ch[c]; p = point[p].fa)
            point[p].ch[c] = np;
        if (!p)
            point[np].fa = 1;
        else
        {
            int q = point[p].ch[c];
            if (point[p].len + 1 == point[q].len)
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
    struct Edge
    {
        int next, to;
    } edge[N];
    int head[N], num_edge;
    inline void add_edge(int from, int to)
    {
        edge[++num_edge].next = head[from];
        edge[num_edge].to = to;
        head[from] = num_edge;
    }
    inline void dfs(int u)
    {
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            dfs(v);
            root[u] = merge(root[u], root[v], 1, n);
        }
    }
    inline void work()
    {
        for (int i = 2; i <= tot; ++i)
            add_edge(point[i].fa, i);
        dfs(1);
    }
    inline void solve(char *s, int l, int r)
    {
        for (int i = 1, u = 1, now = 0; s[i]; ++i)
        {
            int c = s[i] - 'a';
            while (u > 1 && !point[u].ch[c])
            {
                u = point[u].fa;
                now = point[u].len;
            }
            if (!point[u].ch[c])
            {
                maxlen[i] = 0;
                continue;
            }
            u = point[u].ch[c];
            ++now;
            while (u > 1)
            {
                if (query(root[u], 1, n, l + now - 1, r))
                    break;
                if (--now == point[point[u].fa].len)
                    u = point[u].fa;
            }
            //			printf("%d %d %d\n",i,u,now);
            maxlen[i] = now;
        }
    }
}
namespace SAM2
{
    struct SAM
    {
        int fa, len, ch[26];
    } point[N];
    int tot = 1, las = 1;
    int nmsl[N];
    inline void insert(int c, int len)
    {
        int p = las, np = las = ++tot;
        point[np].len = point[p].len + 1;
        nmsl[np] = len;
        for (; p && !point[p].ch[c]; p = point[p].fa)
            point[p].ch[c] = np;
        if (!p)
            point[np].fa = 1;
        else
        {
            int q = point[p].ch[c];
            if (point[p].len + 1 == point[q].len)
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
    struct Edge
    {
        int next, to;
    } edge[N];
    int head[N], num_edge;
    inline void add_edge(int from, int to)
    {
        edge[++num_edge].next = head[from];
        edge[num_edge].to = to;
        head[from] = num_edge;
    }
    ll ans = 0;
    inline void dfs(int u)
    {
        for (int i = head[u]; i; i = edge[i].next)
        {
            int &v = edge[i].to;
            dfs(v);
            nmsl[u] = max(nmsl[u], nmsl[v]);
        }
        ans += point[u].len - point[point[u].fa].len;
        ans -= max(min(nmsl[u], point[u].len) - point[point[u].fa].len, 0);
    }
    inline void work()
    {
        for (int i = 2; i <= tot; ++i)
            add_edge(point[i].fa, i);
        dfs(1);
    }
    inline void init()
    {
        clear(nmsl, 1, tot, 0);
        clear(point, 1, tot, 0);
        clear(head, 1, tot, 0);
        tot = las = 1;
        num_edge = 0;
        ans = 0;
    }
}
char T[N];
inline void work()
{
    int l, r;
    scanf("%s", T + 1), read(l, r);
    SAM1::solve(T, l, r);
    //	for(int i=1; T[i]; ++i)
    //		printf("%d ",maxlen[i]);
    //	putchar('\n');
    for (int i = 1; T[i]; ++i)
        SAM2::insert(T[i] - 'a', maxlen[i]);
    SAM2::work();
    printf("%lld\n", SAM2::ans);
    SAM2::init();
}
signed main()
{
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    scanf("%s", S + 1);
    n = (int)strlen(S + 1);
    for (int i = 1; S[i]; ++i)
        SAM1::insert(S[i] - 'a', i);
    SAM1::work();
    int q;
    read(q);
    while (q--)
        work();
    return 0;
}
