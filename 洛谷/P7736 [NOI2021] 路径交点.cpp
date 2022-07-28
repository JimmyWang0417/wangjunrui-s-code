/**
 *    unicode: UTF-8
 *    name:    P7736 [NOI2021] 路径交点
 *    author:  wangjunrui
 *    created: 2022.07.27 周三 10:15:19 (Asia/Shanghai)
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
constexpr int N = 205;
constexpr int mod = 998244353;
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
        Matrix res(n, rhs.m);
        for (int i = 1; i <= n; ++i)
            for (int k = 1; k <= m; ++k)
                for (int j = 1; j <= rhs.m; ++j)
                    (res.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
        return res;
    }
    inline ll calc()
    {
        bool flag = false;
        for (int i = 1; i <= n; ++i)
        {
            int where = 0;
            for (int j = i; j <= n; ++j)
                if (g[j][i])
                {
                    where = j;
                    break;
                }
            if (where != i)
            {
                swap(g[i], g[where]);
                flag ^= 1;
            }
            ll inv = quickpow(g[i][i], mod - 2);
            for (int j = i + 1; j <= n; ++j)
            {
                ll times = g[j][i] * inv % mod;
                for (int k = i; k <= n; ++k)
                    (g[j][k] -= g[i][k] * times) %= mod;
            }
        }
        ll res = flag ? -1 : 1;
        for (int i = 1; i <= n; ++i)
            (res *= g[i][i]) %= mod;
        return res;
    }
} f, g;
int k, n[N], m[N];
inline void work()
{
    read(k);
    for (int i = 1; i <= k; ++i)
        read(n[i]);
    for (int i = 1; i < k; ++i)
        read(m[i]);
    f = Matrix(n[1], n[1]);
    for (int i = 1; i <= n[1]; ++i)
        f.g[i][i] = 1;
    for (int i = 1; i < k; ++i)
    {
        g = Matrix(n[i], n[i + 1]);
        for (int j = 1; j <= m[i]; ++j)
        {
            int u, v;
            read(u, v);
            g.g[u][v] = 1;
        }
        f = f * g;
    }
    printf("%lld\n", (f.calc() + mod) % mod);
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}