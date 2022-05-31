#include <bits/stdc++.h>
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
constexpr int N = 1005;
constexpr int mod = 1e9 + 7;
int n, m;
char str[N][N];
struct node
{
    ll a, b, c;
    node(ll _a = 0, ll _b = 0, ll _c = 0) : a(_a), b(_b), c(_c) {}
    inline node operator*(const node &rhs) const
    {
        return node(a * rhs.a % mod, (a * rhs.b + b * rhs.c) % mod, c * rhs.c % mod);
    }
};
inline ll quickpow(ll a, ll b)
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
inline node quickpow(node a, ll b)
{
    node res(1, 0, 1);
    while (b)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
signed main()
{
    ll T;
    read(n, m, T);
    for (int i = 1; i <= n; ++i)
        scanf("%s", str[i] + 1);
    int cnt = 0, a = 0, b = 0, c = 0, d = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (str[i][j] == '#')
            {
                ++cnt;
                if (i == 1)
                {
                    if (str[n][j] == '#')
                        ++b;
                }
                else if (str[i - 1][j] == '#')
                    ++a;
                if (j == 1)
                {
                    if (str[i][m] == '#')
                        ++d;
                }
                else if (str[i][j - 1] == '#')
                    ++c;
            }
    if (b && d)
        printf("1\n");
    else if (!b && !d)
        printf("%lld\n", quickpow(cnt, T - 1));
    else
    {
        node res = quickpow(b ? node(cnt, a, b) : node(cnt, c, d), T - 1);
        printf("%lld\n", (res.a - res.b + mod) % mod);
    }
    return 0;
}