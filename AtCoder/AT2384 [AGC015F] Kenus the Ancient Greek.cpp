#include <cstdio>
#include <vector>
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
constexpr int mod = 1e9 + 7;
ll dp[100];
int limit;
vector<pair<ll, ll>> g[100];
signed main()
{
    dp[1] = dp[2] = 1;
    for (limit = 1; (dp[limit + 1] = dp[limit - 1] + dp[limit]) <= (ll)1e18; ++limit)
        ;
    g[1].emplace_back(1ll, 2ll);
    for (int i = 2; i <= limit; ++i)
    {
        g[i].resize(i);
        g[i][i - 1] = make_pair(dp[i + 2], dp[i] + dp[i + 2]);
        for (int j = i - 2; j >= 0; --j)
            g[i][j] = make_pair(g[i - 1][j].second, g[i - 1][j].first + g[i - 1][j].second);
    }
    int q;
    read(q);
    while (q--)
    {
        ll x, y;
        read(x, y);
        if (x > y)
            swap(x, y);
        int res;
        for (res = 2; g[res].front().first <= x && g[res].front().second <= y; ++res)
            ;
        --res;
        ll ans = 0;
        for (auto u : g[res])
        {
            if (u.first <= x && u.second <= y)
                ans += (y - u.second) / u.first + 1;
            if (u.second <= x)
                ans += (x - u.second) / u.first + 1;
            ans %= mod;
        }
        if (res == 1)
            (ans += x) %= mod;
        printf("%d %lld\n", res, ans);
    }
    return 0;
}