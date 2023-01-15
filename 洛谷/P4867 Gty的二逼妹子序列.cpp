/**
 *    unicode: UTF-8
 *    name:    P4867 Gty的二逼妹子序列
 *    author:  whitepaperdog
 *    created: 2022.07.01 周五 19:51:55 (Asia/Shanghai)
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
constexpr int N = 1e5 + 5, M = 1e6 + 5;
int n, m, a[N];
int block, num, belong[N], L[N], R[N];
int cnt[N], blockcnt[N];
struct node
{
    int l, r, a, b, id;
    inline bool operator<(const node &rhs) const
    {
        return belong[l] == belong[rhs.l] ? (belong[l] & 1 ? r < rhs.r : r > rhs.r) : l < rhs.l;
    }
} b[M];
int answer[M];
signed main()
{
    read(n, m);
    block = (int)__builtin_sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
    {
        read(b[i].l, b[i].r, b[i].a, b[i].b);
        b[i].id = i;
    }
    sort(b + 1, b + 1 + m);
    for (int kase = 1, l = 1, r = 0; kase <= m; ++kase)
    {
        int ql = b[kase].l, qr = b[kase].r, qa = b[kase].a, qb = b[kase].b, &res = answer[b[kase].id];
        while (l > ql)
        {
            if (!cnt[a[--l]]++)
                ++blockcnt[belong[a[l]]];
        }
        while (r < qr)
        {
            if (!cnt[a[++r]]++)
                ++blockcnt[belong[a[r]]];
        }
        while (l < ql)
        {
            if (!--cnt[a[l]])
                --blockcnt[belong[a[l]]];
            ++l;
        }
        while (r > qr)
        {
            if (!--cnt[a[r]])
                --blockcnt[belong[a[r]]];
            --r;
        }
        if (belong[qa] == belong[qb])
        {
            for (int i = qa; i <= qb; ++i)
                if (cnt[i])
                    ++res;
        }
        else
        {
            for (int i = R[belong[qa]]; i >= qa; --i)
                if (cnt[i])
                    ++res;
            for (int i = belong[qa] + 1; i < belong[qb]; ++i)
                res += blockcnt[i];
            for (int i = L[belong[qb]]; i <= qb; ++i)
                if (cnt[i])
                    ++res;
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}