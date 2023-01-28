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
ll all;
struct node
{
    int b, l, r;
    ll ans;
    inline bool operator<(const node &rhs) const
    {
        return ans > rhs.ans;
    }
} a[N];
ll sum[N];
inline bool check(ll val)
{
    if (val % m == 0)
        return sum[min(val / m, (ll)n)] >= all;
    else
    {
        ll b = val % m;
        for (int i = 1; i <= n; ++i)
        {
            ll now = (b <= a[i].b ? (ll)b * a[i].l : (ll)a[i].b * a[i].l + (ll)(b - a[i].b) * a[i].r);
            if ((i <= val / m ? sum[min(val / m + 1, (ll)n)] - a[i].ans + now : sum[min(val / m, (ll)n)] + now) >= all)
                return true;
        }
        return false;
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);
#endif
    read(n, m);
    ll cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].b, a[i].l, a[i].r);
        cnt += a[i].b;
        all += (ll)a[i].b * a[i].l;
        a[i].ans = (ll)a[i].b * a[i].l + (ll)(m - a[i].b) * a[i].r;
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + a[i].ans;
    ll l = 0, r = cnt, ans = 0;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
