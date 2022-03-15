#include <cstdio>
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
constexpr int N = 531441 + 5;
inline void exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
        x = 1, y = 0;
    else
    {
        exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
}
int n, m, t;
int mod;
struct node
{
    ll x, y;
    node(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
    inline node operator+(const node &rhs) const
    {
        return node((x + rhs.x) % mod, (y + rhs.y) % mod);
    }
    inline node operator*(const node &rhs) const
    {
        return node((x * rhs.x - y * rhs.y) % mod, (x * rhs.y + y * rhs.x - y * rhs.y) % mod);
    }
};
inline node quickpow(node a, int b)
{
    node res(1, 0);
    while (b)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
inline void FWT(node *f)
{
    for (int k = 1; k * 3 <= n; k *= 3)
        for (int i = 0; i < n; i += k * 3)
            for (int j = 0; j < k; ++j)
            {
                node x = f[i + j], y = f[i + j + k], z = f[i + j + k + k];
                f[i + j] = x + y + z;
                f[i + j + k] = x + y * node(0, 1) + z * node(-1, -1);
                f[i + j + k + k] = x + y * node(-1, -1) + z * node(0, 1);
            }
}
inline void IFWT(node *f)
{
    for (int k = 1; k * 3 <= n; k *= 3)
        for (int i = 0; i < n; i += k * 3)
            for (int j = 0; j < k; ++j)
            {
                node x = f[i + j], y = f[i + j + k], z = f[i + j + k + k];
                f[i + j] = x + y + z;
                f[i + j + k] = x + y * node(-1, -1) + z * node(0, 1);
                f[i + j + k + k] = x + y * node(0, 1) + z * node(-1, -1);
            }
}
node f[N], g[N];
int a[15][15];
signed main()
{
    read(m, t, mod);
    n = 1;
    for (int i = 0; i < m; ++i, n *= 3)
        ;
    for (int i = 0; i < n; ++i)
        read(f[i].x);
    for (int i = 0; i <= m; ++i)
        for (int j = 0; i + j <= m; ++j)
            read(a[i][j]);
    for (int i = 0; i <= n; ++i)
    {
        int x = i;
        int s1 = 0, s2 = 0;
        while (x)
        {
            if (x % 3 == 1)
                ++s1;
            else if (x % 3 == 2)
                ++s2;
            x /= 3;
        }
        g[i].x = a[s1][s2];
    }
    FWT(f), FWT(g);
    for (int i = 0; i < n; ++i)
        f[i] = f[i] * quickpow(g[i], t);
    IFWT(f);
    int x, y;
    exgcd(n, mod, x, y);
    for (int i = 0; i < n; ++i)
        printf("%lld\n", (f[i].x * x % mod + mod) % mod);
    return 0;
}