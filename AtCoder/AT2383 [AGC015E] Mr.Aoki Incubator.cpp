#include <algorithm>
#include <cstdio>
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
constexpr int mod = 1e9 + 7;
int n;
struct node
{
    int x, v;
} a[N];
int L[N], R[N];
int p[N], mp[N];
int f[N], g[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i].x, a[i].v);
        p[i] = a[i].x;
    }
    sort(a + 1, a + 1 + n, [](const node &x, const node &y)
         { return x.v < y.v; });
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; ++i)
    {
        a[i].x = (int)(lower_bound(p + 1, p + 1 + n, a[i].x) - p);
        L[a[i].x] = R[a[i].x] = i;
    }
    for (int i = 2; i <= n; ++i)
        ckmax(R[i], R[i - 1]);
    for (int i = n - 1; i >= 1; --i)
        ckmin(L[i], L[i + 1]);
    int lef = 0;
    f[0] = g[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        while (R[lef] < L[i] - 1)
            ++lef;
        f[i] = (g[i - 1] - g[lef - 1] + mod) % mod;
        g[i] = (g[i - 1] + f[i]) % mod;
    }
    while (R[lef] < n)
        ++lef;
    printf("%d\n", (g[n] - g[lef - 1] + mod) % mod);
    return 0;
}
