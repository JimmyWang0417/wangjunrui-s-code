/**
 *    unicode: UTF-8
 *    name:    AT3948 [AGC022C] Remainder Game
 *    author:  wangjunrui
 *    created: 2022.07.12 周二 08:21:24 (Asia/Shanghai)
 **/
#include <bitset>
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
constexpr int N = 55;
int n, a[N], b[N];
bitset<N> vis[N], exist;
inline bool check()
{
    for (int i = 1; i <= n; ++i)
    {
        vis[i].reset();
        vis[i][a[i]] = true;
    }
    for (int i = 50; i >= 1; --i)
    {
        if (exist[i])
            for (int j = 1; j <= n; ++j)
                for (int k = a[j]; k >= i; --k)
                    if (vis[j][k])
                        vis[j][k % i] = true;
    }
    for (int i = 1; i <= n; ++i)
        if (!vis[i][b[i]])
            return false;
    return true;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    exist.set();
    if (!check())
        printf("-1\n");
    else
    {
        ll res = 0;
        for (int i = 50; i >= 1; --i)
        {
            exist[i] = false;
            if (!check())
            {
                exist[i] = true;
                res |= (1ll << i);
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}