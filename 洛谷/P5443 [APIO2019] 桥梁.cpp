/**
 *    unicode: UTF-8
 *    name:    P5443 [APIO2019] 桥梁
 *    author:  whitepaperdog
 *    created: 2022.07.25 周一 16:52:13 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <vector>
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
constexpr int N = 1e5 + 5;
int n, m, q;
struct Edge
{
    int u, v, w;
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
} a[N];
struct Query
{
    int opt, x, y, id;
} b[N];
int block, num, L[N], R[N];
Edge c[N], d[N];
int totc, totd;
int vis[N];
int p[N], tot;

int e[N], tote;

int size[N];
struct union_set
{
    int fa[N];
    inline int find(int x)
    {
        return !fa[x] ? x : fa[x] = find(fa[x]);
    }
} fa, belong;
pair<int, int> st[N];
int top;
int answer[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
        read(a[i].u, a[i].v, a[i].w);
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        read(b[i].opt, b[i].x, b[i].y);
        b[i].id = i;
    }

    block = (int)__builtin_sqrt(m);
    num = (q - 1) / block + 1;

    L[0] = 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = R[i - 1] + block;
    }
    R[num] = q;

    for (int kase = 1; kase <= num; ++kase)
    {
        fill(size + 1, size + 1 + n, 1);
        totc = totd = tote = 0;
        for (int i = L[kase]; i <= R[kase]; ++i)
            if (b[i].opt == 1)
            {
                c[++totc] = Edge(b[i].x, b[i].y, b[i].id);
                vis[b[i].x] = kase;
            }
            else
                d[++totd] = Edge(b[i].x, b[i].y, b[i].id);
        int qwq = 0;
        for (int i = 1; i <= tot; ++i)
        {
            if (vis[p[i]] == kase)
                continue;
            p[++qwq] = p[i];
        }
        tot = qwq;
        for (int i = 1; i <= m; ++i)
            if (vis[i] == kase - 1)
                p[++tot] = i;
            else if (vis[i] == kase)
                e[++tote] = i;
        auto compare = [](int x, int y)
        { return a[x].w > a[y].w; };
        sort(p + 1 + qwq, p + 1 + tot, compare);
        inplace_merge(p + 1, p + 1 + qwq, p + 1 + tot, compare);
        sort(d + 1, d + 1 + totd, [](Edge x, Edge y)
             { return x.v > y.v; });
        int k = 1;
        for (int i = 1, j = 1; i <= totd; ++i)
        {
            while (j <= tot && a[p[j]].w >= d[i].v)
            {
                int x = fa.find(belong.find(a[p[j]].u)),
                    y = fa.find(belong.find(a[p[j]].v));
                if (x != y)
                {
                    belong.fa[x] = y;
                    size[y] += size[x];
                }
                ++j;
            }
            while (k <= totc && c[k].w <= d[i].w)
            {
                swap(a[c[k].u].w, c[k].v);
                ++k;
            }
            while (k > 1 && c[k - 1].w > d[i].w)
            {
                --k;
                swap(a[c[k].u].w, c[k].v);
            }
            for (int l = 1; l <= tote; ++l)
                if (d[i].v <= a[e[l]].w)
                {
                    int x = fa.find(belong.find(a[e[l]].u)),
                        y = fa.find(belong.find(a[e[l]].v));
                    if (x != y)
                    {
                        fa.fa[x] = y;
                        size[y] += size[x];
                        st[++top] = make_pair(x, y);
                    }
                }
            answer[d[i].w] = size[fa.find(belong.find(d[i].u))];
            while (top)
            {
                fa.fa[st[top].first] = 0;
                size[st[top].second] -= size[st[top].first];
                --top;
            }
        }
        while (k <= totc)
        {
            a[c[k].u].w = c[k].v;
            ++k;
        }
        fill(belong.fa + 1, belong.fa + 1 + n, 0);
    }
    for (int i = 1; i <= q; ++i)
        if (answer[i])
            printf("%d\n", answer[i]);
    return 0;
}