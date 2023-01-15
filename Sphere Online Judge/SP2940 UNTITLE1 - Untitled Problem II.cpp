/**
 *    unicode: UTF-8
 *    name:    SP2940 UNTITLE1 - Untitled Problem II
 *    author:  whitepaperdog
 *    created: 2022.07.07 周四 20:26:26 (Asia/Shanghai)
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
constexpr int N = 5e4 + 5;
int n, m;
ll a[N], tag[N], add[N];
int block, num, L[N], R[N], belong[N];
int q[N], tail[N];
inline void pushup(int bel)
{
    tail[bel] = L[bel] - 1;
    for (int i = L[bel]; i <= R[bel]; ++i)
    {
        while (tail[bel] > L[bel] &&
               (q[tail[bel] - 1] - q[tail[bel]]) * (a[i] - a[q[tail[bel]]]) <=
                   (a[q[tail[bel] - 1]] - a[q[tail[bel]]]) * (i - q[tail[bel]]))
            --tail[bel];
        q[++tail[bel]] = i;
    }
    // for (int i = L[bel]; i <= tail[bel]; ++i)
    //     printf("%d ", q[i]);
    // putchar('\n');
}
inline void pushdown(int bel)
{
    for (int i = L[bel]; i <= R[bel]; ++i)
        a[i] += add[bel] + tag[bel] * (i - L[bel]);
    add[bel] = tag[bel] = 0;
}
inline void update(int l, int r, int val)
{
    if (belong[l] == belong[r])
    {
        pushdown(belong[l]);
        for (int i = l; i <= r; ++i)
            a[i] += (i - l + 1) * val;
        for (int i = r + 1; i <= R[belong[r]]; ++i)
            a[i] += (r - l + 1) * val;
        pushup(belong[r]);
        for (int i = belong[r] + 1; i <= num; ++i)
            add[i] += (r - l + 1) * val;
        return;
    }
    pushdown(belong[l]);
    for (int i = l; i <= R[belong[l]]; ++i)
        a[i] += (i - l + 1) * val;
    pushup(belong[l]);
    for (int i = belong[l] + 1; i < belong[r]; ++i)
    {
        add[i] += (L[i] - l + 1) * val;
        tag[i] += val;
    }
    pushdown(belong[r]);
    for (int i = L[belong[r]]; i <= r; ++i)
        a[i] += (i - l + 1) * val;
    for (int i = r + 1; i <= R[belong[r]]; ++i)
        a[i] += (r - l + 1) * val;
    pushup(belong[r]);
    for (int i = belong[r] + 1; i <= num; ++i)
        add[i] += (r - l + 1) * val;
}
inline ll query(int bel)
{
    int l = L[bel], r = tail[bel] - 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (a[q[mid]] + q[mid] * tag[bel] <= a[q[mid + 1]] + q[mid + 1] * tag[bel])
            l = mid + 1;
        else
            r = mid - 1;
    }
    return a[q[l]] + add[bel] + tag[bel] * (q[l] - L[bel]);
}
inline ll query(int l, int r)
{
    if (belong[l] == belong[r])
    {
        ll res = -1e18;
        for (int i = l; i <= r; ++i)
            ckmax(res, a[i] + add[belong[l]] + tag[belong[l]] * (i - L[belong[l]]));
        return res;
    }
    ll res = -1e18;
    for (int i = l; i <= R[belong[l]]; ++i)
        ckmax(res, a[i] + add[belong[l]] + tag[belong[l]] * (i - L[belong[l]]));
    for (int i = belong[l] + 1; i < belong[r]; ++i)
        ckmax(res, query(i));
    for (int i = L[belong[r]]; i <= r; ++i)
        ckmax(res, a[i] + add[belong[r]] + tag[belong[r]] * (i - L[belong[r]]));
    return res;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    read(m);
    for (int i = 2; i <= n; ++i)
        a[i] += a[i - 1];
    block = (int)__builtin_sqrt(n * __builtin_log2(n));
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
        pushup(i);
    }
    for (int i = 1; i <= m; ++i)
    {
        int opt, l, r, v;
        read(opt, l, r);
        if (opt)
            printf("%lld\n", query(l, r));
        else
        {
            read(v);
            update(l, r, v);
        }
    }
    return 0;
}