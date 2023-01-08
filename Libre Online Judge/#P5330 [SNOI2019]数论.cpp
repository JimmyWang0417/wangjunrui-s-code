/**
 *    unicode: UTF-8
 *    name:    P5330 [SNOI2019]数论
 *    author:  wangjunrui
 *    created: 2022.07.26 周二 15:10:21 (Asia/Shanghai)
 **/
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
constexpr int N = 1e6 + 5;
int p, q, n, m, limit;
ll T;
int a[N], b[N];
bool mp[N];
int Log[N];
int dp[N][22];
signed main()
{
    read(p, q, n, m, T);
    for (int i = 0; i < n; ++i)
    {
        read(a[i]);
        mp[a[i]] = true;
    }
    for (int i = 0; i < m; ++i)
    {
        read(b[i]);
        dp[b[i]][0] = 1;
    }
    // for (ll i = 0; i < T; ++i)
    //     printf("%lld %lld %lld %d\n", i, i % p, i % q, mp[i % p] && dp[i % q][0]);
    // putchar('\n');
    limit = q;
    Log[0] = -1;
    for (int i = 1; i <= limit; ++i)
        Log[i] = Log[i >> 1] + 1;
    for (int j = 1; j <= Log[limit]; ++j)
        for (int i = 0; i < q; ++i)
            dp[i][j] = dp[i][j - 1] + dp[(i + (ll)(1 << (j - 1)) * p) % q][j - 1];
    ll ans = 0;
    for (int i = 0; i < p; ++i)
        if (mp[i])
        {
            ll len = (T - 1 - i) / p + 1;
            if (len >= limit)
            {
                int qwq = 0;
                for (int j = Log[limit]; j >= 0; --j)
                    if ((limit >> j) & 1)
                        qwq += dp[(i + (ll)(((1 << j) - 1) & limit) * p) % q][j];
                ans += qwq * (len / limit);
                len %= limit;
            }
            for (int j = Log[len]; j >= 0; --j)
                if ((len >> j) & 1)
                    ans += dp[(i + (ll)(((1 << j) - 1) & len) * p) % q][j];
        }
    printf("%lld\n", ans);
    return 0;
}