/**
 *    unicode: UTF-8
 *    name:    #6490. 「XXOI 2018」暑假时在做什么？有没有空？可以来学物理吗？
 *    author:  whitepaperdog
 *    created: 2022.07.22 周五 10:12:35 (Asia/Shanghai)
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
constexpr int N = 1e5 + 5;
int n, nmsl, wdnmd;
ll a[N], b[N], c[N], d[N], e[N];
int block, num, L[N], R[N], belong[N];
inline ll query(int l, int r)
{
    if (belong[l] == belong[r])
    {
        ll res = -1e18;
        for (int i = l; i <= r; ++i)
            ckmax(res, a[i] + max(c[i], d[belong[i]]));
        return res;
    }
    ll res = -1e18;
    for (int i = R[belong[l]]; i >= l; --i)
        ckmax(res, a[i] + max(c[i], d[belong[i]]));
    for (int i = belong[l] + 1; i < belong[r]; ++i)
        ckmax(res, e[i]);
    for (int i = L[belong[r]]; i <= r; ++i)
        ckmax(res, a[i] + max(c[i], d[belong[i]]));
    return res;
}
inline void update(int l, int r, ll v)
{
    if (belong[l] == belong[r])
    {
        for (int i = l; i <= r; ++i)
        {
            ckmax(c[i], v);
            ckmax(e[belong[i]], a[i] + c[i]);
        }
        return;
    }

    for (int i = R[belong[l]]; i >= l; --i)
    {
        ckmax(c[i], v);
        ckmax(e[belong[i]], a[i] + c[i]);
    }
    for (int i = belong[l] + 1; i < belong[r]; ++i)
    {
        ckmax(d[i], v);
        ckmax(e[i], b[i] + d[i]);
    }
    for (int i = L[belong[r]]; i <= r; ++i)
    {
        ckmax(c[i], v);
        ckmax(e[belong[i]], a[i] + c[i]);
    }
}
signed main()
{
    read(n, nmsl, wdnmd);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        a[i] += a[i - 1];
    }
    block = (int)__builtin_sqrt(n + 1);
    num = n / block + 1;
    R[0] = -1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    memset(b, ~0x3f, sizeof(b));
    memset(c, ~0x3f, sizeof(c));
    memset(d, ~0x3f, sizeof(d));
    memset(e, ~0x3f, sizeof(e));
    for (int i = 0; i <= n; ++i)
        ckmax(b[belong[i]], a[i]);
    update(nmsl, wdnmd, 0);
    for (int i = 1; i <= n; ++i)
    {
        printf("%lld ", query(i, n));
        int l = i + nmsl, r = i + wdnmd;
        ckmin(r, n);
        if (l <= r)
            update(l, r, -a[i]);
    }
    putchar('\n');
    return 0;
}