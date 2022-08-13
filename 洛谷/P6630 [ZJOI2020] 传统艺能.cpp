/**
 *    unicode: UTF-8
 *    name:    A. 三色二叉树
 *    author:  wangjunrui
 *    created: 2022.07.29 周五 09:57:04 (Asia/Shanghai)
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
constexpr int N = 2e5 + 5;
constexpr int mod = 998244353;
inline ll calc(int x)
{
    return (ll)x * (x + 1) / 2 % mod;
}
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
    ll g[3][3];
    Matrix() { memset(g, 0, sizeof(g)); }
    inline Matrix operator*(const Matrix &rhs) const
    {
        Matrix res;
        for (int i = 0; i < 3; ++i)
            for (int k = 0; k < 3; ++k)
                for (int j = 0; j < 3; ++j)
                    (res.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
        return res;
    }
    inline Matrix operator^(int power) const
    {
        Matrix res, a = (*this);
        for (int i = 0; i < 3; ++i)
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
    inline ll *operator[](int x)
    {
        return g[x];
    }
    inline void print()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
                printf("%lld ", g[i][j]);
            putchar('\n');
        }
    }
} dp;
int n, m;
int a[N], tot;
int root, lc[N], rc[N];
inline void dfs(int &rt, int l, int r)
{
    if (l == r)
        return;
    rt = ++tot;
    dfs(lc[rt], l, a[rt]);
    dfs(rc[rt], a[rt] + 1, r);
}
ll answer;
inline void solve(int rt, int l, int r, ll fasum, ll g, ll h, ll inv)
{
    ll p1 = fasum,                                                                    //覆盖该区间但是不访问
        p2 = g,                                                                       //不覆盖该区间但是父亲的标记会下传
        p3 = h,                                                                       //不覆盖父亲
        p4 = (ll)l * (n - r + 1) % mod * inv % mod,                                   //覆盖该区间
        p5 = ((ll)(r - l) * (n - r + l - 1) + calc(r - l + 1) - 1) % mod * inv % mod; //穿过该区间
    dp[0][0] = (p2 + p3 + p5) % mod, dp[0][1] = p1, dp[0][2] = (p4 - p1) % mod;
    dp[1][0] = p5, dp[1][1] = (p1 + p3) % mod, dp[1][2] = (p2 + p4 - p1) % mod;
    dp[2][0] = p5, dp[2][1] = 0, dp[2][2] = (p2 + p3 + p4) % mod;
    (answer += (dp ^ m).g[0][2]) %= mod;
    if (l == r)
        return;
    h = (calc(l - 1) + calc(n - r)) % mod * inv % mod;
    solve(lc[rt], l, a[rt], p4, ((ll)(r - a[rt]) * (n - r) + calc(r - a[rt])) % mod * inv % mod, h, inv);
    solve(rc[rt], a[rt] + 1, r, p4, ((ll)(a[rt] - l + 1) * (l - 1) + calc(a[rt] - l + 1)) % mod * inv % mod, h, inv);
}
signed main()
{
    read(n, m);
    for (int i = 1; i < n; ++i)
        read(a[i]);
    dfs(root, 1, n);
    solve(root, 1, n, 0, 0, 0, quickpow(calc(n), mod - 2));
    printf("%lld\n", (answer + mod) % mod);
    return 0;
}