#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
const int N = 2e5 + 5;
int n, m, a[N], p[N];
int cnt[N], num[N];
int block, belong[N];
struct Queue
{
    int l, r, id;
    inline bool operator<(const Queue &rhs) const
    {
        return belong[l] == belong[rhs.l] ? (belong[l] & 1 ? r < rhs.r : r > rhs.r) : belong[l] < belong[rhs.l];
    }
} q[N];
int ans = 0;
inline void add(int pos)
{
    --num[cnt[a[pos]]];
    ++num[++cnt[a[pos]]];
    ans = max(ans, cnt[a[pos]]);
}
inline void del(int pos)
{
    --num[cnt[a[pos]]];
    ++num[--cnt[a[pos]]];
    if (!num[ans])
        --ans;
}
int answer[N];
signed main()
{
    read(n, m);
    block = (int)sqrt(n);
    for (re int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[i] = a[i];
        belong[i] = (i - 1) / block + 1;
    }
    sort(p + 1, p + 1 + n);
    int tot = (int)(unique(p + 1, p + 1 + n) - 1 - p);
    for (re int i = 1; i <= n; ++i)
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
    for (re int i = 1; i <= m; ++i)
    {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for (re int i = 1; i <= m; ++i)
    {
        const int &ql = q[i].l, &qr = q[i].r;
        while (ql < l)
            add(--l);
        while (ql > l)
            del(l++);
        while (qr < r)
            del(r--);
        while (qr > r)
            add(++r);
        answer[q[i].id] = -ans;
    }
    for (re int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}
