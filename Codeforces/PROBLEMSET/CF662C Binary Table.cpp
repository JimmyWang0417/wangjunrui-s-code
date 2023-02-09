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
constexpr int N = (1 << 20) + 5;
int n, m;
ll a[N], b[N];
int g[N], popcount[N];
char str[N];
inline void FWT(ll *A)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (1 << n); ++j)
            if ((j >> i) & 1)
            {
                ll x = A[(1 << i) ^ j], y = A[j];
                A[(1 << i) ^ j] = x + y, A[j] = x - y;
            }
}
inline void IFWT(ll *A)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (1 << n); ++j)
            if ((j >> i) & 1)
            {
                ll x = A[(1 << i) ^ j], y = A[j];
                A[(1 << i) ^ j] = (x + y) / 2, A[j] = (x - y) / 2;
            }
}
signed main()
{
    read(n, m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", str);
        for (int j = 0; j < m; ++j)
            if (str[j] == '1')
                g[j] |= (1 << i);
    }
    for (int i = 0; i < m; ++i)
        ++a[g[i]];
    for (int i = 1; i < (1 << n); i++)
        popcount[i] = popcount[i >> 1] + (i & 1);
    for (int i = 0; i < (1 << n); ++i)
        b[i] = min(popcount[i], n - popcount[i]);
    FWT(a), FWT(b);
    for (int i = 0; i < (1 << n); ++i)
        a[i] *= b[i];
    IFWT(a);
    ll res = n * m;
    for (int i = 0; i < (1 << n); ++i)
        ckmin(res, a[i]);
    printf("%lld\n", res);
    return 0;
}