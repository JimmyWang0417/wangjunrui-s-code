#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 105;
const int mod = 1e9 + 7;
inline ll quickpow(ll a, int b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Matrix
{
    ll g[N][N];
    int n, m;
    Matrix(int _n = 0, int _m = 0) : n(_n), m(_m) { memset(g, 0, sizeof(g)); }
    inline Matrix operator*(const Matrix &rhs) const
    {
        Matrix ans(n, rhs.m);
        for (int i = 0; i <= n; ++i)
            for (int k = 0; k <= m; ++k)
            {
                for (int j = 0; j <= rhs.m; ++j)
                    (ans.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
            }
        return ans;
    }
    inline Matrix operator^(int power) const
    {
        Matrix ans(n, n), a = (*this);
        for (int i = 0; i <= n; ++i)
            ans.g[i][i] = 1;

        while (power)
        {
            if (power & 1)
                ans = ans * a;
            a = a * a;
            power >>= 1;
        }
        return ans;
    }
    inline void print()
    {
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= m; ++j)
                printf("%lld ", g[i][j]);
            putchar('\n');
        }
        putchar('\n');
    }
} g;
int n, m, k, a[N];
signed main()
{
    read(n, k);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        m += 1 - a[i];
    }
    ll inv = quickpow(n * (n - 1) / 2, mod - 2);
    int x = 0;
    for (int i = 1; i <= m; ++i)
        x += 1 - a[i];
    g = Matrix(m, m);
    for (int i = max(m - (n - m), 0); i <= m; ++i)
    {
        int l0 = i, r0 = m - i, l1 = m - l0, r1 = n - m - r0;
        g.g[i][i] = ((l0 + l1) * (l0 + l1 - 1) / 2 + (r0 + r1) * (r0 + r1 - 1) / 2 + l0 * r0 + l1 * r1) * inv % mod;
        g.g[i][i + 1] = r0 * l1 * inv % mod;
        g.g[i][i - 1] = l0 * r1 * inv % mod;
    }
    printf("%lld\n", (g ^ k).g[x][m]);
    return 0;
}