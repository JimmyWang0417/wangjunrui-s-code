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
constexpr int N = 3e5 + 5;
int n, a[N];
ll sumb[N], sumc[N];
int tot;
ll p[N];
pair<ll, ll> b[N];
int c[N];
inline void update(int pos, int val)
{
    for (int i = pos; i <= tot; i += lowbit(i))
        ckmax(c[i], val);
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        ckmax(res, c[i]);
    return res;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("clyz.in", "r", stdin);
    freopen("clyz.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 2; i <= n; ++i)
    {
        int x;
        read(x);
        sumb[i] = sumb[i - 1] + x;
    }
    for (int i = 2; i <= n; ++i)
    {
        int x;
        read(x);
        if (x < sumb[i] - sumb[i - 1])
        {
            printf("-1\n");
            return 0;
        }
        sumc[i] = sumc[i - 1] + x;
    }
    for (int i = 1; i <= n; ++i)
    {
        b[i] = make_pair(a[i] - sumc[i], a[i] - sumb[i]);
        p[i] = b[i].second;
    }
    sort(p + 1, p + 1 + n);
    sort(b + 1, b + 1 + n, [](const pair<ll, ll> &lhs, const pair<ll, ll> &rhs)
         { return lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first > rhs.first; });
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
    {
        int pos = (int)(lower_bound(p + 1, p + 1 + tot, b[i].second) - p);
        update(pos, query(pos) + 1);
    }
    printf("%d\n", n - query(tot));
    return 0;
}
