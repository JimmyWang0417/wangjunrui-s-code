#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
#define ll long long
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
inline void read(T &x, T1 &... x1)
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
int a[N], b[N];
int root[N], cnt;
int belong[N], block, num;
int L[N], R[N];
ll answer[N];
struct node
{
    int l, r, ql, qr, id;
    inline bool operator<(const node &rhs) const
    {
        return belong[l] == belong[rhs.l] ? r < rhs.r : l < rhs.l;
    }
} c[N];
struct NODE
{
    int belong[N], block, num;
    int L[N], R[N];
    ll sum[N];
    ll max[N];
    inline void init()
    {
        block = (int)sqrt(m);
        num = (m - 1) / block + 1;
        for (int i = 1; i <= num; ++i)
        {
            L[i] = R[i - 1] + 1;
            R[i] = min(R[i - 1] + block, m);
            for (int j = L[i]; j <= R[i]; ++j)
                belong[j] = i;
        }
    }
    inline void update(int pos, int val) { ckmax(max[belong[pos]], sum[pos] += val); }
    inline ll query(int l, int r)
    {
        if (belong[l] == belong[r])
        {
            ll res = 0;
            for (int i = l; i <= r; ++i)
                ckmax(res, sum[i]);
            return res;
        }
        ll res = 0;
        for (int i = l; i <= R[belong[l]]; ++i)
            ckmax(res, sum[i]);
        for (int i = belong[l] + 1; i < belong[r]; ++i)
            ckmax(res, max[i]);
        for (int i = L[belong[r]]; i <= r; ++i)
            ckmax(res, sum[i]);
        return res;
    }
    inline void clear()
    {
        memset(sum, 0, sizeof(sum));
        memset(max, 0, sizeof(max));
    }
} lzx;
ll sum[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("GOAT.in","r",stdin);
    freopen("GOAT.out","w",stdout);
#endif
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    block = (int)sqrt(n);
    num = (n - 1) / block + 1;
    for (int i = 1; i <= num; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = min(R[i - 1] + block, n);
        for (int j = L[i]; j <= R[i]; ++j)
            belong[j] = i;
    }
    lzx.init();
    for (int i = 1; i <= q; ++i)
    {
        read(c[i].l, c[i].r, c[i].ql, c[i].qr);
        c[i].id = i;
    }
    sort(c + 1, c + 1 + q);
    for (int i = 1, lastblock = 0, r = 0; i <= q; ++i)
    {
        if (belong[c[i].l] != lastblock)
        {
            r = R[lastblock = belong[c[i].l]];
            lzx.clear();
        }
        if (belong[c[i].l] == belong[c[i].r])
        {
            for (int j = c[i].l; j <= c[i].r; ++j)
                if (c[i].ql <= a[j] && a[j] <= c[i].qr)
                    ckmax(answer[c[i].id], sum[a[j]] += b[j]);
            for (int j = c[i].l; j <= c[i].r; ++j)
                sum[a[j]] = 0;
            continue;
        }
        while (r < c[i].r)
        {
            ++r;
            lzx.update(a[r], b[r]);
        }
        answer[c[i].id] = lzx.query(c[i].ql, c[i].qr);
        for (int j = c[i].l; j <= R[belong[c[i].l]]; ++j)
            if (c[i].ql <= a[j] && a[j] <= c[i].qr)
            {
                sum[a[j]] += b[j];
                ckmax(answer[c[i].id], lzx.sum[a[j]] + sum[a[j]]);
            }
        for (int j = c[i].l; j <= R[belong[c[i].l]]; ++j)
            sum[a[j]] = 0;
    }
    for (int i = 1; i <= q; ++i)
        printf("%lld\n", answer[i]);
    return 0;
}
