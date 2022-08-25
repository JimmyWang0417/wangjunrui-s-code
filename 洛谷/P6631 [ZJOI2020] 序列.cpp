/**
 *    unicode: UTF-8
 *    name:    P6631 [ZJOI2020] 序列
 *    author:  wangjunrui
 *    created: 2022.08.26 周五 01:08:53 (Asia/Shanghai)
 **/
#include <algorithm>
#include <bits/move.h>
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
constexpr int N = 1e5 + 5;
int n, a[N];
ll _buf[2][2][2][2];
signed main()
{
    auto f = _buf[0], g = _buf[1];
    int T = 1;
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)
            read(a[i]);
        memset(f, ~0x3f, sizeof(_buf[0]));
        f[0][0][0] = 0;
        f[1][1][0] = a[1];
        for (int i = 2; i <= n; ++i)
        {
            swap(f, g);
            memset(f, ~0x3f, sizeof(_buf[0]));
            if (i & 1)
            {
                for (int j = 0; j <= 1; ++j)
                    for (int k = 0; k <= 1; ++k)
                        for (int l = 0; l <= 1; ++l)
                            for (int r = -1; r <= 1; ++r)
                                if (j + r <= 1 && k + r <= 1)
                                    ckmax(f[max(max(j + r, r), 0)][max(max(k + r, r), 0)][l], g[j][k][l] + a[i] * r);
            }
            else
            {
                for (int j = 0; j <= 1; ++j)
                    for (int k = 0; k <= 1; ++k)
                        for (int l = 0; l <= 1; ++l)
                            for (int r = -1; r <= 1; ++r)
                                if (j + r <= 1 && l + r <= 1)
                                    ckmax(f[max(max(j + r, r), 0)][k][max(max(l + r, r), 0)], g[j][k][l] + a[i] * r);
            }
        }
        ll res = -1e18;
        for (int j = 0; j <= 1; ++j)
            for (int k = 0; k <= 1; ++k)
                for (int l = 0; l <= 1; ++l)
                    ckmax(res, f[j][k][l]);
        printf("%lld\n", res);
    }
    return 0;
}