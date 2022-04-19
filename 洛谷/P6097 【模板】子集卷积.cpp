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
constexpr int N = 25, M = (1 << 20) + 5;
constexpr int mod = 1e9 + 9;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void dec(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n;
int A[N][M], B[N][M], C[N][M];
int g[M];
inline void FWT(int *dp)
{
    for (int i = 0; i < n; ++i)
        for (int S = 0; S < (1 << n); ++S)
            if ((S >> i) & 1)
                add(dp[S], dp[S ^ (1 << i)]);
}
inline void IFWT(int *dp)
{
    for (int i = 0; i < n; ++i)
        for (int S = 0; S < (1 << n); ++S)
            if ((S >> i) & 1)
                dec(dp[S], dp[S ^ (1 << i)]);
}
signed main()
{
    read(n);
    for (int i = 1; i < (1 << n); ++i)
        g[i] = g[i ^ lowbit(i)] + 1;
    for (int i = 0; i < (1 << n); ++i)
        read(A[g[i]][i]);
    for (int i = 0; i < (1 << n); ++i)
        read(B[g[i]][i]);
    for (int i = 0; i <= n; ++i)
    {
        FWT(A[i]);
        FWT(B[i]);
    }
    for (int i = 0; i <= n; ++i)
        for (int j = 0; i + j <= n; ++j)
            for (int S = 0; S < (1 << n); ++S)
                add(C[i + j][S], (int)((ll)A[i][S] * B[j][S] % mod));
    for (int i = 0; i <= n; ++i)
        IFWT(C[i]);
    for (int i = 0; i < (1 << n); ++i)
        printf("%d ", C[g[i]][i]);
    putchar('\n');
    return 0;
}