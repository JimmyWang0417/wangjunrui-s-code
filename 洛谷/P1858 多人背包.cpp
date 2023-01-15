/**
 *    unicode: UTF-8
 *    name:    P1858 多人背包
 *    author:  whitepaperdog
 *    created: 2022.08.12 周五 08:51:57 (Asia/Shanghai)
 **/
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
constexpr int N = 205, M = 5e4 + 5;
int n, m, k;
struct node
{
    ll a[50];
    node() { memset(a, ~0x3f, sizeof(a)); }
    inline void update(const node &rhs, int add)
    {
        node lhs(*this);
        for (int i = 0, j = 0, l = 0; i < k; ++i)
            a[i] = lhs.a[j] > rhs.a[l] + add ? lhs.a[j++] : rhs.a[l++] + add;
    }
    inline ll calc() const
    {
        ll res = 0;
        for (int i = 0; i < k; ++i)
            res += a[i];
        return res;
    }
} dp[M];
signed main()
{
    read(k, m, n);
    dp[0].a[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        read(x, y);
        for (int j = m; j >= x; --j)
            dp[j].update(dp[j - x], y);
    }
    printf("%lld\n", dp[m].calc());
    return 0;
}