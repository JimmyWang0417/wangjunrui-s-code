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
constexpr int N = 1e5 + 5;
int n, m, a[N];
ll k;
struct node
{
    int g[N];
    node()
    {
        memset(g, 0, sizeof(g));
    }
    inline int &operator[](const int x)
    {
        return g[x];
    }
    inline void operator*=(node rhs)
    {
        for (int i = 1; i < n; ++i)
            g[i] = rhs.g[g[i]];
    }
    inline node operator^(ll power)
    {
        node res, now = (*this);
        for (int i = 1; i < n; ++i)
            res.g[i] = i;
        while (power)
        {
            if (power & 1)
                res *= now;
            now *= now;
            power >>= 1;
        }
        return res;
    }
    inline void print()
    {
        for (int i = 1; i < n; ++i)
            printf("%d ", g[i]);
        putchar('\n');
    }
} g;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = n; i >= 2; --i)
        a[i] -= a[i - 1];
    read(m, k);
    for (int i = 1; i < n; ++i)
        g[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int x;
        read(x);
        swap(g[x - 1], g[x]);
    }
    g = g ^ k;
    ll res = a[1];
    printf("%lld\n", res);
    for (int i = 2; i <= n; ++i)
        printf("%lld\n", res += a[g[i - 1] + 1]);
    return 0;
}