#include <algorithm>
#include <cstdio>
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
constexpr int N = 1e5 + 5;
int n, m;
int a[N], b[N], c[N], d[N], e[N];
ll sum[N];
signed main()
{
    read(n, m);
    for (int i = 2; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
        read(b[i]);
    for (int i = 1; i <= n; ++i)
        read(c[i]);
    for (int i = 2; i <= m; ++i)
        read(d[i]);
    ll res = 0;
    for (int i = 2; i <= n; ++i)
        res += a[i] + b[1];
    for (int i = 2; i <= m; ++i)
        res += c[1] + d[i];
    ll cnt = 0;
    for (int i = 2; i <= m; ++i)
        cnt += b[i];
    for (int i = 2; i <= m; ++i)
        e[i] = d[i] - b[i];
    sort(e + 2, e + 1 + m);
    for (int i = 2; i <= m; ++i)
        sum[i] = sum[i - 1] + e[i];
    for (int i = 2; i <= n; ++i)
    {
        int pos = (int)(upper_bound(e + 2, e + 1 + m, a[i] - c[i]) - e - 1);
        res += cnt + sum[pos] + (ll)(pos - 1) * c[i] + (ll)(m - pos) * a[i];
    }
    printf("%lld\n", res);
    return 0;
}