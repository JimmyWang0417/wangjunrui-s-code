/**
 *    unicode: UTF-8
 *    name:    CF1372E Omkar and Last Floor
 *    author:  wangjunrui
 *    created: 2022.07.10 周日 01:03:45 (Asia/Shanghai)
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
constexpr int N = 105;
int n, m;
int f[N][N], g[N][N][N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int cnt;
        read(cnt);
        for (int j = 1; j <= cnt; ++j)
        {
            int x, y;
            read(x, y);
            for (int k = x; k <= y; ++k)
                ++g[k][x][y];
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        for (int j = m; j >= 1; --j)
            for (int k = j; k <= m; ++k)
                g[i][j][k] += g[i][j][k - 1];
        for (int j = m; j >= 1; --j)
            for (int k = j; k <= m; ++k)
                g[i][j][k] += g[i][j + 1][k];
    }
    for (int len = 1; len <= m; ++len)
        for (int l = 1; l + len - 1 <= m; ++l)
        {
            int r = l + len - 1;
            for (int i = l; i <= r; ++i)
                ckmax(f[l][r], f[l][i - 1] + g[i][l][r] * g[i][l][r] + f[i + 1][r]);
        }
    printf("%d\n", f[1][m]);
    return 0;
}