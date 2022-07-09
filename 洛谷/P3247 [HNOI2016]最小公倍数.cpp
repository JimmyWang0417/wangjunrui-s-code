/**
 *    unicode: UTF-8
 *    name:    P3247 [HNOI2016]最小公倍数
 *    author:  wangjunrui
 *    created: 2022.07.06 周三 17:14:54 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e5 + 5, M = 5e4 + 5;
int n, m, q;
struct Edge
{
    int u, v, a, b;
    Edge(int _u = 0, int _v = 0, int _a = 0, int _b = 0) : u(_u), v(_v), a(_a), b(_b) {}
    inline bool operator<(const Edge &rhs) const { return a == rhs.a ? b < rhs.b : a < rhs.a; }
} edge[N], e[N], st[N];
int tot;
int fa[N], ancestor[N], a[N], b[N];
inline int get(int x)
{
    return !ancestor[x] ? x : ancestor[x] = get(ancestor[x]);
}
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
struct Query
{
    int u, v, a, b, belong, id;
    inline bool operator<(const Query &rhs) const { return belong == rhs.belong ? b < rhs.b : belong < rhs.belong; }
} c[N];
int block, num, L[N], R[N], belong[N];
int top;
bool answer[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
        read(edge[i].u, edge[i].v, edge[i].a, edge[i].b);
    read(q);
    sort(edge + 1, edge + 1 + m);
    block = (int)__builtin_sqrt((double)m * m / q);
    num = (int)(m - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, m);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    belong[m + 1] = num + 1;
    for (int i = 1; i <= q; ++i)
    {
        read(c[i].u, c[i].v, c[i].a, c[i].b);
        c[i].belong = belong[upper_bound(edge + 1, edge + 1 + m, Edge(c[i].u, c[i].v, c[i].a, c[i].b)) - edge] - 1;
        c[i].id = i;
    }
    sort(c + 1, c + 1 + q);
    auto compare = [](const Edge &lhs, const Edge &rhs)
    { return lhs.b < rhs.b; };
    fill(a + 1, a + 1 + n, -1);
    fill(b + 1, b + 1 + n, -1);
    for (int kase = 1, qwq = 1; kase <= q; ++kase)
    {
        if (c[kase].belong != c[kase - 1].belong)
        {
            for (int j = c[kase - 1].belong + 1; j <= c[kase].belong; ++j)
                for (int i = L[j]; i <= R[j]; ++i)
                    e[i] = edge[i];
            sort(e + 1 + R[c[kase - 1].belong], e + 1 + R[c[kase].belong], compare);
            inplace_merge(e + 1, e + 1 + R[c[kase - 1].belong], e + 1 + R[c[kase].belong], compare);
            fill(ancestor + 1, ancestor + 1 + n, 0);
            fill(a + 1, a + 1 + n, -1);
            fill(b + 1, b + 1 + n, -1);
            qwq = 1;
        }
        while (e[qwq].b <= c[kase].b && qwq <= R[c[kase].belong])
        {
            int x = get(e[qwq].u), y = get(e[qwq].v);
            if (x == y)
            {
                ckmax(a[y], e[qwq].a);
                ckmax(b[y], e[qwq].b);
            }
            else
            {
                ancestor[x] = y;
                ckmax(a[y], max(a[x], e[qwq].a));
                ckmax(b[y], max(b[x], e[qwq].b));
            }
            ++qwq;
        }
        for (int j = L[c[kase].belong + 1]; j <= R[c[kase].belong + 1] && edge[j].a <= c[kase].a; ++j)
            if (edge[j].b <= c[kase].b)
            {
                int x = find(get(edge[j].u)), y = find(get(edge[j].v));
                st[++top] = Edge(x, y, a[y], b[y]);
                if (x == y)
                {
                    ckmax(a[y], edge[j].a);
                    ckmax(b[y], edge[j].b);
                }
                else
                {
                    fa[x] = y;
                    ckmax(a[y], max(a[x], edge[j].a));
                    ckmax(b[y], max(b[x], edge[j].b));
                }
            }
        int x = find(get(c[kase].u)), y = find(get(c[kase].v));
        if (x == y)
            if (a[x] == c[kase].a && b[x] == c[kase].b)
                answer[c[kase].id] = 1;
        while (top)
        {
            fa[st[top].u] = 0;
            a[st[top].v] = st[top].a;
            b[st[top].v] = st[top].b;
            --top;
        }
    }
    for (int i = 1; i <= q; ++i)
        puts(answer[i] ? "Yes" : "No");
    return 0;
}