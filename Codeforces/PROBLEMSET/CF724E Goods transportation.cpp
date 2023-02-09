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
constexpr int N = 10005;
int n, c, p[N], s[N];
ll a[N];
signed main()
{
    read(n, c);
    ll now = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(p[i]);
        now += p[i];
    }
    for (int i = 1; i <= n; ++i)
        read(s[i]);
    for (int i = 1; i <= n; ++i)
        a[i] = (ll)(n - i) * c + s[i] - p[i];
    ll res = now;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        ckmin(res, now += a[i] - (ll)(i - 1) * c);
    printf("%lld\n", res);
    return 0;
}