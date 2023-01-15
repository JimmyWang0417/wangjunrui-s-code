/**
 *    unicode: UTF-8
 *    name:    AT4378 [AGC027D] Modulo Matrix
 *    author:  whitepaperdog
 *    created: 2022.07.31 周日 21:12:20 (Asia/Shanghai)
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
constexpr int N = 505;
int n;
ll a[1001][1001];
int prime[2003], tot;
bool vis[100005];
inline void init(int limit)
{
    for (int i = 2; i <= limit; ++i)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > limit)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}
inline ll __lcm(ll a, ll b)
{
    if (!a || !b)
        return a | b;
    return a / __gcd(a, b) * b;
}
signed main()
{
    init(10000);
    read(n);
    if (n == 2)
    {
        printf("4 7\n23 10\n");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = (i + 1 & 1) + 1; j <= n; j += 2)
            a[i][j] = (ll)prime[(i + j) / 2] * prime[n + (i - j) / 2 + (n + 1) / 2];
    for (int i = 1; i <= n; ++i)
        for (int j = (i & 1) + 1; j <= n; j += 2)
            a[i][j] = __lcm(__lcm(a[i - 1][j], a[i + 1][j]), __lcm(a[i][j - 1], a[i][j + 1])) + 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            printf("%lld ", a[i][j]);
        putchar('\n');
    }
    return 0;
}