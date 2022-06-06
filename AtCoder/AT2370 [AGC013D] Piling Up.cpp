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
constexpr int N = 3e3 + 5;
constexpr int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m;
int f[N][2], g[N][2];
signed main()
{
    read(n, m);
    for (int i = 0; i <= n; ++i)
        f[i][i == 0] = 1;
    for (int i = 0; i < m; ++i)
    {
        memset(g, 0, sizeof(g));
        for (int j = 0; j <= n; ++j)
        {
            if (j > 0)
            {
                add(g[j - 1][j == 1], f[j][0]);
                add(g[j - 1][1], f[j][1]);
                add(g[j][j == 1], f[j][0]);
                add(g[j][1], f[j][1]);
            }
            if (j < n)
            {
                add(g[j][0], f[j][0]);
                add(g[j][1], f[j][1]);
                add(g[j + 1][0], f[j][0]);
                add(g[j + 1][1], f[j][1]);
            }
        }
        memcpy(f, g, sizeof(g));
    }
    int res = 0;
    for (int i = 0; i <= n; ++i)
        add(res, f[i][1]);
    printf("%d\n", res);
    return 0;
}