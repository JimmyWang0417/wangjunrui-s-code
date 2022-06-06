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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
struct node
{
    int n, m;
    ll g[3][3];
    node(int _n = 0, int _m = 0) : n(_n), m(_m) { memset(g, 0, sizeof(g)); }
    inline ll *operator[](int rhs)
    {
        return g[rhs];
    }
    inline node operator*(const node &rhs) const
    {
        node res(n, rhs.m);
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < m; ++k)
                for (int j = 0; j < rhs.m; ++j)
                    (res.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
        return res;
    }
    inline node operator^(int power) const
    {
        node res(n, n), a = (*this);
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
};
int n, m, a[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
        read(a[i]);
    node f(1, 3), mark(3, 3), unmark(3, 3);
    f[0][0] = f[0][1] = f[0][2] = 1;
    mark[0][0] = 1, mark[0][1] = 0, mark[0][2] = 0;
    mark[1][0] = 2, mark[1][1] = 1, mark[1][2] = 0;
    mark[2][0] = 1, mark[2][1] = 1, mark[2][2] = 1;
    unmark[0][0] = 2, unmark[0][1] = 1, unmark[0][2] = 1;
    unmark[1][0] = 2, unmark[1][1] = 1, unmark[1][2] = 0;
    unmark[2][0] = 1, unmark[2][1] = 1, unmark[2][2] = 1;
    if (m)
    {
        f = f * (unmark ^ (a[1] - 1));
        for (int i = 1; i < m; ++i)
            f = f * mark * (unmark ^ (a[i + 1] - a[i] - 1));
        printf("%lld\n", (f * mark * (unmark ^ (n - a[m] - 1))).g[0][0]);
    }
    else
        printf("%lld\n", (f * (unmark ^ (n - 1))).g[0][0]);
    return 0;
}
