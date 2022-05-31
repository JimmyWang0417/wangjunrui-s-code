#include <algorithm>
#include <climits>
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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void del(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n;
ll a[N], A, B;
int dp[N];
int q[N];
ll f[N][25];
int Log[N];
inline ll query(int l, int r)
{
    if (l > r)
        return LONG_LONG_MAX / 2;
    int k = Log[r - l + 1];
    return min(f[l][k], f[r - (1 << k) + 1][k]);
}
signed main()
{
    read(n, A, B);
    if (A < B)
        swap(A, B);
    a[0] = LONG_LONG_MIN / 2;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    a[n + 1] = LONG_LONG_MAX / 2;
    for (int i = 1; i + 1 < n; ++i)
        if (a[i + 2] - a[i] < B)
        {
            printf("0\n");
            return 0;
        }
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
        Log[i] = Log[i >> 1] + 1;
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
        f[i][0] = a[i + 1] - a[i];
    for (int j = 1; j <= Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    for (int i = 1, l = 0, r = 1, sum = 1; i <= n + 1; ++i)
    {
        while (a[i] - a[r] >= #include <algorithm>
#include <climits>
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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void del(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n;
ll a[N], A, B;
int dp[N];
signed main()
{
    read(n, A, B);
    if (A < B)
        swap(A, B);
    a[0] = LONG_LONG_MIN / 2;
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    a[n + 1] = LONG_LONG_MAX / 2;
    for (int i = 1; i + 1 < n; ++i)
        if (a[i + 2] - a[i] < B)
        {
            printf("0\n");
            return 0;
        }
    dp[0] = 1;
    for (int i = 1, j = 0, sum = 0; i <= n + 1; ++i)
    {
        while (a[i] - a[j] >= A)
            add(sum, dp[j++]);
        dp[i] = sum;
        if (a[i] - a[i - 1] < B)
        {
            sum = 0;
            j = i - 1;
        }
    }
    printf("%d\n", dp[n + 1]);
    return 0;
}A)
            add(sum, dp[r++]);
        while (query(l + 1, i - 2) < B)
            del(sum, dp[l++]);
        dp[i] = sum;
    }
    printf("%d\n", dp[n + 1]);
    return 0;
}