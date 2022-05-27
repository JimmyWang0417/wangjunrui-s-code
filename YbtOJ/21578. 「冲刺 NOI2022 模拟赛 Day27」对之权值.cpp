#include <algorithm>
#include <climits>
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
constexpr int N = 2e5 + 5;
int n;
struct node
{
    int a, b;
} a[N];
inline ll solve1()
{
    int maxx = a[n].a, minn = a[0].b;
    for (int i = 1; i < n; ++i)
    {
        ckmax(maxx, a[i].a);
        ckmin(minn, a[i].b);
    }
    return (ll)(maxx - a[0].a) * (a[n].b - minn);
}
inline ll solve2()
{
    sort(a + 1, a + n, [](const node &x, const node &y)
         { return x.a < y.a; });
    int maxx = max(a[n - 1].a, max(a[0].b, a[n].a)), minn = min(a[0].b, a[n].a), res = INT_MAX;
    for (int i = 1; i < n; ++i)
    {
        ckmin(res, maxx - min(minn, a[i].a));
        ckmax(maxx, a[i].b);
        ckmin(minn, a[i].b);
    }
    return (ll)(a[n].b - a[0].a) * res;
}
inline ll solve3()
{
    int maxx = a[n].a, minn = a[0].b;
    for (int i = 1; i < n; ++i)
    {
        ckmax(maxx, a[i].a);
        ckmin(minn, a[i].b);
    }
    return (ll)(maxx - a[0].a) * (a[0].b - minn);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("pair.in", "r", stdin);
    freopen("pair.out", "w", stdout);
#endif
    read(n);
    for (int i = 0; i < n; ++i)
        read(a[i].a, a[i].b);
    for (int i = 0; i < n; ++i)
        if (a[i].a > a[i].b)
            swap(a[i].a, a[i].b);
    sort(a, a + n, [](const node &x, const node &y)
         { return x.a < y.a; });
    sort(a + 1, a + n, [](const node &x, const node &y)
         { return x.b < y.b; });
    if (a[0].b <= a[n - 1].b)
    {
        --n;
        printf("%lld\n", min(solve1(), solve2()));
    }
    else
        printf("%lld\n", solve3());
    return 0;
}
