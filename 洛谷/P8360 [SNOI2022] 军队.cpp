/**
 *    unicode: UTF-8
 *    name:    P8360 [SNOI2022] 军队
 *    author:  whitepaperdog
 *    created: 2022.07.28 周四 16:28:57 (Asia/Shanghai)
 **/
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
constexpr int N = 2.5e5 + 5;
int n, q, C;
ll a[N], b[N];
int c[N];
int belong[N];
int block, num, L[N], R[N];
struct node
{
    int opt, l, r, x, y;
} d[N];
ll answer[N];
int fa[N], size[N];
inline int find(int x)
{
    if (!fa[x])
        return x;
    int _fa = fa[x];
    fa[x] = find(fa[x]);
    if (fa[_fa])
    {
        a[x] += b[_fa];
        b[x] += b[_fa];
    }
    return fa[x];
}
inline void build(int kase)
{
    for (int i = L[kase]; i <= R[kase]; ++i)
    {
        size[i] = 1;
        if (belong[c[i]])
        {
            fa[i] = belong[c[i]];
            ++size[belong[c[i]]];
        }
        else
            belong[c[i]] = i;
    }
}
inline void pushdown(int kase)
{
    for (int i = L[kase]; i <= R[kase]; ++i)
    {
        a[i] += b[find(i)];
        belong[c[i] = c[find(i)]] = 0;
    }
    for (int i = L[kase]; i <= R[kase]; ++i)
        b[i] = fa[i] = 0;
}
int cnt[N];
signed main()
{
    // freopen("project.in", "r", stdin);
    // freopen("project.out", "w", stdout);
    read(n, q, C);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(c[i]);
    for (int i = 1; i <= q; ++i)
    {
        read(d[i].opt, d[i].l, d[i].r);
        if (d[i].opt != 3)
            read(d[i].x, d[i].y);
    }
    block = (int)(0.5 * __builtin_sqrt(n));
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = R[i - 1] + block;
    }
    R[num] = n;
    for (int kase = 1; kase <= num; ++kase)
    {
        ll res = 0;
        for (int i = L[kase]; i <= R[kase]; ++i)
            res += a[i];
        build(kase);
        for (int i = 1; i <= q; ++i)
            if (d[i].opt == 1)
            {
                if (d[i].x == d[i].y)
                    continue;
                if (d[i].l <= L[kase] && R[kase] <= d[i].r)
                {
                    if (belong[d[i].x])
                    {
                        if (belong[d[i].y])
                        {
                            int x = find(belong[d[i].x]), y = find(belong[d[i].y]);
                            b[x] -= b[y];
                            a[x] += b[x];
                            fa[x] = y;
                            size[y] += size[x];
                        }
                        else
                            c[belong[d[i].y] = belong[d[i].x]] = d[i].y;
                        belong[d[i].x] = 0;
                    }
                }
                else if (belong[d[i].x] && max(d[i].l, L[kase]) <= min(d[i].r, R[kase]))
                {
                    pushdown(kase);
                    for (int j = max(L[kase], d[i].l); j <= R[kase] && j <= d[i].r; ++j)
                        if (c[j] == d[i].x)
                            c[j] = d[i].y;
                    build(kase);
                }
            }
            else if (d[i].opt == 2)
            {
                if (d[i].l <= L[kase] && R[kase] <= d[i].r)
                {
                    if (belong[d[i].x])
                    {
                        b[find(belong[d[i].x])] += d[i].y;
                        res += (ll)size[find(belong[d[i].x])] * d[i].y;
                    }
                }
                else if (belong[d[i].x] && max(d[i].l, L[kase]) <= min(d[i].r, R[kase]))
                {
                    pushdown(kase);
                    for (int j = max(L[kase], d[i].l); j <= R[kase] && j <= d[i].r; ++j)
                        if (c[j] == d[i].x)
                        {
                            a[j] += d[i].y;
                            res += d[i].y;
                        }
                    build(kase);
                }
            }
            else
            {
                if (d[i].l <= L[kase] && R[kase] <= d[i].r)
                    answer[i] += res;
                else if (max(d[i].l, L[kase]) <= min(d[i].r, R[kase]))
                {
                    pushdown(kase);
                    for (int j = max(L[kase], d[i].l); j <= R[kase] && j <= d[i].r; ++j)
                        answer[i] += a[j] + b[find(j)];
                    build(kase);
                }
            }
        pushdown(kase);
    }
    for (int i = 1; i <= q; ++i)
        if (d[i].opt == 3)
            printf("%lld\n", answer[i]);
    return 0;
}