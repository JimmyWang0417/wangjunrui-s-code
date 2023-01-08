#include <cstdio>
#include <cstring>
#define ll long long
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
constexpr int N = 1005;
int mod;
struct Matrix
{
    ll g[3][3];
    int n, m;
    Matrix(int _n = 0, int _m = 0) : n(_n), m(_m) { memset(g, 0, sizeof(g)); }
    inline Matrix operator*(const Matrix &rhs) const
    {
        Matrix res(n, rhs.m);
        for (int i = 0; i < res.n; ++i)
            for (int k = 0; k < m; ++k)
                for (int j = 0; j < res.m; ++j)
                    (res.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
        return res;
    }
    inline Matrix operator^(int power) const
    {
        Matrix res(n, n), a = (*this);
        for (int i = 0; i < n; ++i)
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
} f(1, 3), g(3, 3);
int n, t, a[N][N];
int h[N], l[N], all;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
#endif
    read(n, t, mod);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            read(a[i][j]);
            a[i][j] %= mod;
        }
    f.g[0][0] = 1;
    g.g[0][0] = 2, g.g[1][0] = 2 * (n - 1);
    g.g[0][1] = 1, g.g[1][1] = n, g.g[2][1] = (n - 1);
    g.g[1][2] = 2, g.g[2][2] = 2 * (n - 1);
    f = f * (g ^ t);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            (h[i] += a[i][j]) %= mod;
            (l[j] += a[i][j]) %= mod;
            (all += a[i][j]) %= mod;
        }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int res = (int)((f.g[0][0] * a[i][j] + f.g[0][1] * (h[i] + l[j] - 2 * a[i][j]) + f.g[0][2] * (all - h[i] - l[j] + a[i][j])) % mod);
            if (res < 0)
                res += mod;
            printf("%d ", res);
        }
        putchar('\n');
    }
    return 0;
}
