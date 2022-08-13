/**
 *    unicode: UTF-8
 *    name:    P4495 [HAOI2018]奇怪的背包
 *    author:  wangjunrui
 *    created: 2022.08.09 周二 20:56:06 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <unordered_map>
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
constexpr int N = 2e3 + 5, M = 1e6 + 5;
constexpr int mod = 1e9 + 7;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, q, p;
int a[N];
int dp[N][N];
unordered_map<int, int> mp;
int cnt[N];
int power[M];
int b[N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    read(n, q, p);
    for (int i = 1; i * i <= p; ++i)
        if (p % i == 0)
        {
            a[++m] = i;
            if (i * i != p)
                a[++m] = p / i;
        }
    sort(a + 1, a + 1 + m);
    for (int i = 1; i <= m; ++i)
        mp[a[i]] = i;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        x = __gcd(x, p);
        ++cnt[mp[x]];
    }
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power[i] = power[i - 1];
        add(power[i], power[i - 1]);
    }
    dp[0][m] = 1;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            add(dp[i][j], dp[i - 1][j]);
            add(dp[i][mp[__gcd(a[i], a[j])]], (int)((ll)dp[i - 1][j] * (power[cnt[i]] - 1) % mod));
        }
    }
    for (int i = 1; i <= m; ++i)
        if (dp[m][i])
        {
            for (int j = 1; j <= m; ++j)
                if (a[j] % a[i] == 0)
                    add(b[j], dp[m][i]);
        }
    while (q--)
    {
        int x;
        read(x);
        x = __gcd(x, p);
        printf("%d\n", b[mp[x]]);
    }
    return 0;
}