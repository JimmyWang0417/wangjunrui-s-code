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
using namespace std;
const int N = 20;
ll n, m;
int mod;
struct Matrix
{
    ll g[N][N];
    int n, m;
    Matrix(int _n = 0, int _m = 0) : n(_n), m(_m) { memset(g, 0, sizeof(g)); }
    inline Matrix operator*(const Matrix &rhs) const
    {
        Matrix ans(n, rhs.m);
        for (int i = 1; i <= n; ++i)
            for (int k = 1; k <= m; ++k)
                for (int j = 1; j <= rhs.m; ++j)
                    (ans.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
        return ans;
    }
    inline Matrix operator^(ll power) const
    {
        --power;
        Matrix res = (*this), a = (*this);
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
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
                printf(" %lld", g[i][j]);
            putchar('\n');
        }
    }
} f, a;
int k, b[N], c[N];
int sum[N];
inline ll solve(ll n)
{
    if (n <= k)
        return sum[n];
    return (f * (a ^ (n - k))).g[1][k + 1];
}
signed main()
{
    read(k);
    for (int i = 1; i <= k; ++i)
        read(b[i]);
    for (int i = 1; i <= k; ++i)
        read(c[i]);
    read(m, n, mod);
    for (int i = 1; i <= k; ++i)
        sum[i] = (sum[i - 1] + b[i]) % mod;
    f = Matrix(1, k + 1), a = Matrix(k + 1, k + 1);
    for (int i = 1; i <= k; ++i)
        f.g[1][i] = b[i];
    f.g[1][k + 1] = sum[k];
    for (int i = 1; i < k; ++i)
        a.g[i + 1][i] = 1;
    for (int i = 1; i <= k; ++i)
        a.g[i][k] = c[k - i + 1];
    for (int i = 1; i <= k; ++i)
        a.g[i][k + 1] = c[k - i + 1];
    a.g[k + 1][k + 1] = 1;
    printf("%lld\n", (solve(n) - solve(m - 1) + mod) % mod);
    return 0;
}