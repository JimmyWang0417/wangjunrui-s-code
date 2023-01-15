/**
 *    unicode: UTF-8
 *    name:    P5322 [BJOI2019] 排兵布阵
 *    author:  whitepaperdog
 *    created: 2022.08.12 周五 09:54:50 (Asia/Shanghai)
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
constexpr int N = 105, M = 2e4 + 5;
int a[N][N];
int f[M], g[M];
signed main()
{
    int s, n, m;
    read(s, n, m);
    for (int i = 1; i <= s; ++i)
        for (int j = 1; j <= n; ++j)
            read(a[j][i]);
    for (int i = 1; i <= n; ++i)
    {
        sort(a[i] + 1, a[i] + 1 + s);
        memcpy(g, f, sizeof(f));
        for (int l = 1, r; l <= s; l = r)
        {
            r = l + 1;
            while (r <= s && a[l] == a[r])
                ++r;
            int x = a[i][l] * 2 + 1, y = (r - 1) * i;
            for (int j = m; j >= x; --j)
                ckmax(f[j], g[j - x] + y);
        }
    }
    printf("%d\n", f[m]);
    return 0;
}