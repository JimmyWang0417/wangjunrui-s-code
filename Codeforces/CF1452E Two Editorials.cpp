#include <bits/stdc++.h>
#include <bits/extc++.h>
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
const int N = 2005;
int n, m, k;
struct node
{
    int l, r;
    inline bool operator<(const node &rhs) const
    {
        return l + r < rhs.l + rhs.r;
    }
} a[N];
ll answer[N];
signed main()
{
    read(n, m, k);
    for (int i = 1; i <= m; ++i)
    {
        read(a[i].l, a[i].r);
        --a[i].l;
    }
    sort(a + 1, a + 1 + m);
    for (int i = 0; i <= n - k; ++i)
    {
        ll now = 0;
        for (int j = m; j >= 1; --j)
        {
            now += max(0, min(a[j].r, i + k) - max(a[j].l, i));
            ckmax(answer[j], now);
        }
    }
    ll res = 0;
    for (int i = 0; i <= n - k; ++i)
    {
        ll now = 0;
        for (int j = 1; j <= m; ++j)
        {
            now += max(0, min(a[j].r, i + k) - max(a[j].l, i));
            ckmax(res, now + answer[j + 1]);
        }
    }
    printf("%lld\n", res);
    return 0;
}