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
int n, m;
int tot;
ll a[N];
ll b[N], c[N];
inline void solve(ll x, ll y)
{
    int pos = (int)(upper_bound(a + 1, a + 1 + tot, x) - a - 1);
    if (!pos)
    {
        c[1] += y;
        c[x + 1] -= y;
    }
    else
    {
        b[pos] += x / a[pos] * y;
        solve(x % a[pos], y);
    }
}
signed main()
{
    read(n, m);
    a[++tot] = n;
    for (int i = 1; i <= m; ++i)
    {
        ll x;
        read(x);
        while (tot && a[tot] >= x)
            --tot;
        a[++tot] = x;
    }
    b[tot] = 1;
    for (int i = tot; i >= 2; --i)
    {
        b[i - 1] += a[i] / a[i - 1] * b[i];
        solve(a[i] % a[i - 1], b[i]);
    }
    c[1] += b[1];
    c[a[1] + 1] -= b[1];
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", c[i] += c[i - 1]);
    return 0;
}