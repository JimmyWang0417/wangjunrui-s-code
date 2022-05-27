#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e5 + 5, K = 105;
const int mod = 998244353;
const int INF = 0x3f3f3f3f;
int n, k, len;
int a[N];
int dp[N][K], sumdp[N];
int g[K][N];
signed main()
{
    read(n, k, len);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= k; ++i)
    {
        g[i][0] = INF;
        for (int j = 1; j <= n; ++j)
        {
            if (a[j] == i || a[j] == -1)
                g[i][j] = min(g[i][j - 1], j);
            else
                g[i][j] = INF;
        }
    }
    dp[0][0] = sumdp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            if (g[j][i] <= n)
            {
                dp[i][j] = sumdp[i - 1];
                if (g[j][i] <= i - len + 1)
                    (dp[i][j] -= (sumdp[i - len] - dp[i - len][j]) % mod) %= mod;
            }
            else
                dp[i][j] = 0;
        }
        for (int j = 1; j <= k; ++j)
            (sumdp[i] += dp[i][j]) %= mod;
    }
    printf("%d\n", (sumdp[n] + mod) % mod);
    return 0;
}
