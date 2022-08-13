/**
 *    unicode: UTF-8
 *    name:    P5342 [TJOI2019]甲苯先生的线段树
 *    author:  wangjunrui
 *    created: 2022.08.13 周六 21:31:59 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 55;
inline int calc(ll x)
{
    int res = 0;
    for (; x; x >>= 1)
        ++res;
    return res;
    // return (int)__lg(x) + 1;
}
inline ll query(ll x, ll y)
{
    ll res = 0;
    int dx = calc(x), dy = calc(y);
    if (dx < dy)
    {
        swap(x, y);
        swap(dx, dy);
    }
    while (dx > dy)
    {
        res += x;
        x >>= 1;
        --dx;
    }
    while (x != y)
    {
        res += x + y;
        x >>= 1, y >>= 1;
    }
    return res + x;
}
inline int solve1(ll all, int d)
{
    int res = 0;
    for (int h = 2; h <= d; ++h)
    {
        ll x = all / ((1ll << h) - 1);
        if (!x)
            break;
        if (calc(x) + h - 1 > d)
            continue;
        ll now = all - x * ((1ll << h) - 1);
        for (int i = h - 1; i >= 0; --i)
            if (now >= (1ll << i) - 1)
                now -= (1ll << i) - 1;
        if (!now)
            ++res;
    }
    return res;
}
ll dp[55][105][2];
inline ll solve2(ll all, int d)
{
    ll res = 0;
    for (int h1 = 2; h1 <= d; ++h1)
        for (int h2 = 2; h2 <= d; ++h2)
        {
            ll x = (all - (1ll << (h2 - 1)) + 1) / ((1ll << h1) + (1ll << h2) - 3);
            if (!x)
                break;
            if (calc(x) + max(h1, h2) - 1 > d)
                continue;
            ll QwQ = (all - (1ll << (h2 - 1)) + 1) - x * ((1ll << h1) + (1ll << h2) - 3);
            for (int cnt = 0; cnt <= h1 + h2 - 4; ++cnt)
            {
                ll now = QwQ + cnt;
                if (now & 1)
                    continue;
                int limit = calc(now) + 1;
                memset(dp, 0, sizeof(dp));
                dp[1][0][0] = 1;
                for (int i = 1; i <= limit; ++i)
                    for (int j = 0, jm = min((i - 1) << 1, h1 + h2 - 4); j <= jm; ++j)
                        for (int k = 0; k < 2; ++k)
                            if (dp[i][j][k])
                                for (int a = 0, am = i < h1 - 1 ? 1 : 0; a <= am; ++a)
                                    for (int b = 0, bm = i < h2 - 1 ? 1 : 0; b <= bm; ++b)
                                        if (((k + a + b) & 1) == (now >> i & 1))
                                            dp[i + 1][j + a + b][(k + a + b) >> 1] += dp[i][j][k];
                res += dp[limit + 1][cnt][0];
            }
        }
    return res;
}
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        int d, c;
        ll a, b;
        read(d, a, b, c);
        if (c == 1)
            printf("%lld\n", query(a, b));
        else
        {
            ll res = query(a, b);
            printf("%lld\n", solve1(res, d) + solve2(res, d) - (res >= (1ll << d)));
        }
    }
    return 0;
}