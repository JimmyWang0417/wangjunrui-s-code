#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 5005;
constexpr int mod = 998244353;
typedef pair<int, int> node;
inline void add(node &x, node y)
{
    x.first += y.first;
    if (x.first >= mod)
        x.first -= mod;
    x.second += y.second;
    if (x.second >= mod)
        x.second -= mod;
}
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
char S[N];
node poly[2][N << 1], polyg[N << 1];
node *dp[2] = {poly[0] + N, poly[1] + N}, *g = polyg + N;
signed main()
{
    freopen("distance.in", "r", stdin);
    freopen("distance.out", "w", stdout);
    int n = INT_MIN;
    for (int now = 0; now < 2; ++now)
    {
        scanf("%s", S);
        int len = (int)strlen(S);
        ckmax(n, len);
        node *f = dp[now];
        f[0] = make_pair(1, 0);
        for (int where = len - 1, t = 0; where >= 0; --where, ++t)
        {
            for (int i = -t - 1; i <= t + 1; ++i)
                g[i] = node();
            if (S[where] != 'P')
            {
                for (int i = -t; i <= t; ++i)
                    add(g[i + 1], f[i]);
            }
            if (S[where] != 'V')
            {
                for (int i = -t; i <= 0; ++i)
                    add(g[i - 1], f[i]);
                for (int i = 1; i <= t; ++i)
                {
                    add(g[0].second, f[i].first);
                    add(g[0].second, f[i].second);
                }
            }
            for (int i = -t - 1; i <= t + 1; ++i)
                f[i] = g[i];
        }
    }
    ll ans = 0;
    for (int i = -n; i <= n; ++i)
        (ans += (ll)dp[0][i].first * dp[1][-i].first) %= mod;
    for (int i = n; i > -n; --i)
        add(dp[0][i - 1], dp[0][i]);
    for (int i = -n; i <= n; ++i)
        (ans += (ll)(dp[0][i + 1].first + dp[0][i + 1].second) * (dp[1][-i].first + dp[1][-i].second)) %= mod;
    printf("%lld\n", ans);
    return 0;
}
