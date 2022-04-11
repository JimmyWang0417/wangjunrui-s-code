#include <bitset>
#include <cstring>
#include <iostream>
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
constexpr int N = 28, M = 1e5 + 5, K = (1 << 23) + 5;
int n, m, k;
int q[M];
int Log[K];
int f[K >> 1], where[K >> 1];
#define calc(pos, S) ((S & ((1 << pos) - 1)) | ((S >> (pos + 1)) << pos))
inline void init(int pos, int *dp, int *g, int *h)
{
    where[0] = 1;
    for (int i = 0; i < n; ++i)
        dp[0] += -g[i] + k * h[i];
    f[0] = dp[0];
    for (int S = 1; S < (1 << n); ++S)
    {
        if ((S >> pos) & 1)
            continue;
        int lasS = calc(pos, (S ^ lowbit(S))), trueS = calc(pos, S), nmsl = Log[lowbit(S)];
        where[trueS] = where[lasS] + 1;
        dp[trueS] = dp[lasS] + f[lasS] + (k + 1) * g[nmsl] * where[trueS] - (k - 1) * h[nmsl] * where[trueS];
        f[trueS] = f[lasS] + (k + 1) * g[nmsl] - (k - 1) * h[nmsl];
    }
}
int g[N][N], h[N][N];
int dp[K], add[23][K >> 1];
signed main()
{
    read(m, n, k);
    for (int i = 0; i < n; ++i)
        Log[1 << i] = i;
    for (int i = 1; i <= m; ++i)
    {
        read(q[i]);
        --q[i];
    }
    for (int i = 1; i < m; ++i)
    {
        if (q[i] == q[i + 1])
            continue;
        ++g[q[i]][q[i + 1]];
        ++h[q[i + 1]][q[i]];
    }
    for (int i = 0; i < n; ++i)
        init(i, add[i], g[i], h[i]);
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int S = 0; S < (1 << n); ++S)
        for (int i = 0; i < n; ++i)
        {
            if ((S >> i) & 1)
                continue;
            ckmin(dp[S | (1 << i)], dp[S] + add[i][calc(i, S)]);
        }
    printf("%d\n", dp[(1 << n) - 1]);
    return 0;
}