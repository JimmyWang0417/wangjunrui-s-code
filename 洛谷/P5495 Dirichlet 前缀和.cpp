/**
 *    unicode: UTF-8
 *    name:    P5495 Dirichlet 前缀和
 *    author:  whitepaperdog
 *    created: 2022.07.03 周日 23:12:28 (Asia/Shanghai)
 **/
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
constexpr int N = 2e7 + 5;
int prime[N], tot;
bool vis[N];
inline void getprimes(int limit)
{
    for (int i = 2; i <= limit; ++i)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot && i * prime[j] <= limit; ++j)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}
#define uint unsigned int
uint seed;
inline uint getnext()
{
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}
int n;
uint a[N];
signed main()
{
    read(n, seed);
    getprimes(n);
    for (int i = 1; i <= n; ++i)
        a[i] = getnext();
    for (int i = 1; i <= tot; ++i)
        for (int j = 1; prime[i] * j <= n; ++j)
            a[prime[i] * j] += a[j];
    uint res = 0;
    for (int i = 1; i <= n; ++i)
        res ^= a[i];
    printf("%u\n", res);
    return 0;
}