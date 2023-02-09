#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <queue>
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
int n, m, k, p;
int a[N], b[N];
struct node
{
    ll a;
    int b, c;
    node(ll _a = 0, int _b = 0, int _c = 0) : a(_a), b(_b), c(_c) {}
    inline bool operator<(const node &rhs) const
    {
        return a / b > rhs.a / rhs.b;
    }
};
inline bool check(ll beg)
{
    __gnu_pbds::priority_queue<node> q;
    for (int i = 1; i <= n; ++i)
        if (beg - (ll)b[i] * m < a[i])
            q.push(node(beg, b[i], a[i]));
    for (int i = 1; i <= m && !q.empty(); ++i)
        for (int j = 1; j <= k && !q.empty(); ++j)
        {
            node u = q.top();
            q.pop();
            if (u.a / u.b < i)
                return false;
            u.a += p;
            if (u.a - (ll)u.b * m < u.c)
                q.push(u);
        }
    return q.empty();
}
signed main()
{
    read(n, m, k, p);
    for (int i = 1; i <= n; ++i)
        read(a[i], b[i]);
    ll l = 0, r = 1e18, ans = 0;
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