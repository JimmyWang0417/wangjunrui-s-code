/**
 *    unicode: UTF-8
 *    name:    P3730 曼哈顿交易
 *    author:  whitepaperdog
 *    created: 2022.07.06 周三 19:35:37 (Asia/Shanghai)
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
constexpr int N = 1e5 + 5;
int n, m, a[N];
int p[N], tot;
int block, num, L[N], R[N], belong[N];
int cnt[N];
int b[N], c[N];
struct Query
{
    int l, r, k, id;
    inline bool operator<(const Query &rhs) const
    {
        return belong[l] == belong[rhs.l] ? (belong[l] & 1 ? r < rhs.r : r > rhs.r) : l < rhs.l;
    }
} q[N];
int answer[N];
inline int query(int k)
{
    for (int i = 1; i <= num; k -= b[i++])
        if (b[i] >= k)
        {
            for (int j = L[i]; j <= R[i]; k -= c[j++])
                if (c[j] >= k)
                    return j;
        }
    return -1;
}
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
    {
        read(a[i]);
        p[i] = a[i];
    }
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
    for (int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r, q[i].k);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    for (int kase = 1, l = 1, r = 0; kase <= m; ++kase)
    {
        int ql = q[kase].l, qr = q[kase].r;
        while (l > ql)
        {
            --l;
            --b[belong[cnt[a[l]]]];
            --c[cnt[a[l]]];
            ++cnt[a[l]];
            ++b[belong[cnt[a[l]]]];
            ++c[cnt[a[l]]];
        }
        while (r < qr)
        {
            ++r;
            --b[belong[cnt[a[r]]]];
            --c[cnt[a[r]]];
            ++cnt[a[r]];
            ++b[belong[cnt[a[r]]]];
            ++c[cnt[a[r]]];
        }
        while (l < ql)
        {
            --b[belong[cnt[a[l]]]];
            --c[cnt[a[l]]];
            --cnt[a[l]];
            ++b[belong[cnt[a[l]]]];
            ++c[cnt[a[l]]];
            ++l;
        }
        while (r > qr)
        {
            --b[belong[cnt[a[r]]]];
            --c[cnt[a[r]]];
            --cnt[a[r]];
            ++b[belong[cnt[a[r]]]];
            ++c[cnt[a[r]]];
            --r;
        }
        answer[q[kase].id] = query(q[kase].k);
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}