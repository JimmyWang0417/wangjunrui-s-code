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
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
struct Matrix
{
    ll g[3][3];
    int n, m;
    Matrix(int _n = 0, int _m = 0) : n(_n), m(_m) { memset(g, 0, sizeof(g)); }
    inline Matrix operator*(const Matrix &rhs) const
    {
        Matrix ans(n, rhs.m);
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < m; ++k)
                for (int j = 0; j < m; ++j)
                    (ans.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
        return ans;
    }
    inline Matrix operator^(int power) const
    {
        Matrix ans(n, n), a = (*this);
        for (int i = 0; i < n; ++i)
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
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
                printf("%lld ", g[i][j]);
            putchar('\n');
        }
    }
} f(1, 3), abab(3, 3), baba(3, 3);
int a, b, c, d;
char n[N], m[N];
int dight[N], tot;
Matrix power[15];
inline Matrix solve(Matrix nmsl, char str[N])
{
    tot = (int)strlen(str);
    for (int i = 1; i <= tot; ++i)
        dight[i] = str[tot - i] - '0';
    for (int i = 1; i <= tot; ++i)
        if (dight[i] == 0)
            dight[i] = 9;
        else
        {
            --dight[i];
            break;
        }
    Matrix res = power[0] = Matrix(nmsl.n, nmsl.m);
    for (int i = 0; i < nmsl.n; ++i)
        res.g[i][i] = power[0].g[i][i] = 1;
    for (int i = 1; i <= 10; ++i)
        power[i] = power[i - 1] * nmsl;
    for (int i = tot; i >= 1; --i)
        res = (res ^ 10) * power[dight[i]];
    return res;
}
signed main()
{
    scanf("%s%s", n, m);
    read(a, b, c, d);
    f.g[0][0] = 1, f.g[0][1] = b, f.g[0][2] = d;

    abab.g[0][0] = a, abab.g[1][0] = 1;
    abab.g[1][1] = 1, abab.g[2][2] = 1;

    baba.g[0][0] = c, baba.g[2][0] = 1;
    baba.g[1][1] = 1, baba.g[2][2] = 1;

    abab = solve(abab, m);
    printf("%lld\n", (f * solve(abab * baba, n) * abab).g[0][0]);
    return 0;
}