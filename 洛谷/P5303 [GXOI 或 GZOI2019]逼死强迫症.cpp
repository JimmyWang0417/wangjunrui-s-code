/**
 *    unicode: UTF-8
 *    name:    P5303 [GXOI/GZOI2019]逼死强迫症
 *    author:  wangjunrui
 *    created: 2022.07.25 周一 15:39:43 (Asia/Shanghai)
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
constexpr int mod = 1e9 + 7;
struct Matrix
{
    ll g[30][30];
    inline auto operator[](int rhs)
    {
        return g[rhs];
    }
    Matrix()
    {
        memset(g, 0, sizeof(g));
    }
    inline Matrix operator*(const Matrix &rhs) const
    {
        Matrix res;
        for (int i = 0; i < 27; ++i)
            for (int k = 0; k < 27; ++k)
                for (int j = 0; j < 27; ++j)
                    (res.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
        return res;
    }
    inline Matrix operator^(int power) const
    {
        Matrix res, a = (*this);
        for (int i = 0; i < 27; ++i)
            res.g[i][i] = 1;
        while (power)
        {
            if (power & 1)
                res = res * a;
            a = a * a;
            power >>= 1;
        }
        return res;
    }
    inline void print()
    {
        for (int i = 0; i < 27; ++i)
        {
            for (int j = 0; j < 27; ++j)
                printf("%lld ", g[i][j]);
            putchar('\n');
        }
    }
} f, g;
#define calc(x, y, z) ((x) + (y)*3 + (z)*9)
int n;
signed main()
{
    for (int u = 0; u < 27; ++u)
    {
        int x = u % 3, y = u / 3 % 3, z = u / 9;
        if (x == 0)
        {
            if (y == 0)
            {
                g[u][calc(1, 1, z)] = 1;
                g[u][calc(0, 0, z)] = 1;
                if (z < 2)
                {
                    g[u][calc(2, 1, z + 1)] = 1;
                    g[u][calc(1, 2, z + 1)] = 1;
                }
            }
            else if (y == 1)
            {
                g[u][calc(1, 0, z)] = 1;
                if (z < 2)
                    g[u][calc(2, 0, z + 1)] = 1;
            }
            else
            {
                g[u][calc(1, 1, z)] = 1;
                g[u][calc(0, 0, z)] = 1;
                if (z < 2)
                    g[u][calc(2, 1, z + 1)] = 1;
            }
        }
        else if (x == 1)
        {
            if (y == 0)
            {
                g[u][calc(0, 1, z)] = 1;
                if (z < 2)
                    g[u][calc(0, 2, z + 1)] = 1;
            }
            else if (y == 1)
                g[u][calc(0, 0, z)] = 1;
            else
                g[u][calc(0, 1, z)] = 1;
        }
        else
        {
            if (y == 0)
            {
                g[u][calc(1, 1, z)] = 1;
                g[u][calc(0, 0, z)] = 1;
                if (z < 2)
                    g[u][calc(1, 2, z + 1)] = 1;
            }
            else
                g[u][calc(1, 0, z)] = 1;
        }
    }
    int T;
    read(T);
    while (T--)
    {
        read(n);
        f = g ^ n;
        printf("%lld\n", (f[0][calc(0, 0, 2)] + f[0][calc(2, 0, 2)] + f[0][calc(0, 2, 2)]) % mod);
    }
    return 0;
}