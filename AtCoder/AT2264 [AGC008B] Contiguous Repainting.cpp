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
ll pre[N], suf[N], sum[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        sum[i] = sum[i - 1] + a[i];
        pre[i] = pre[i - 1] + max(a[i], 0);
    }
    for (int i = n; i >= 1; --i)
        suf[i] = suf[i + 1] + max(a[i], 0);
    ll res = 0;
    for (int i = 1; i + m - 1 <= n; ++i)
        ckmax(res, pre[i - 1] + suf[i + m] + max(sum[i + m - 1] - sum[i - 1], 0ll));
    printf("%lld\n", res);
    return 0;
}