/**
 *    unicode: UTF-8
 *    name:    P4141 消失之物
 *    author:  whitepaperdog
 *    created: 2022.08.12 周五 08:14:03 (Asia/Shanghai)
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
constexpr int N = 2005;
int n, m, a[N];
int f[N], g[N];
inline void add(int &x, int y)
{
    x += y;
    if (x >= 10)
        x -= 10;
}
inline void dec(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += 10;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= a[i]; --j)
            add(f[j], f[j - a[i]]);
    for (int i = 1; i <= n; ++i)
    {
        memcpy(g, f, sizeof(f));
        for (int j = a[i]; j <= m; ++j)
            dec(g[j], g[j - a[i]]);
        for (int j = 1; j <= m; ++j)
            printf("%d", g[j]);
        putchar('\n');
    }
    return 0;
}