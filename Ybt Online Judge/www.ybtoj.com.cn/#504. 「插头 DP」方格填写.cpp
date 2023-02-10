#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = (1 << 7) + 5;
constexpr int mod = 998244353;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m;
int dp[2][N][N];
signed main()
{
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdout);
    auto f0 = dp[0], f1 = dp[1];
    int times;
    read(times);
    while (times--)
    {
        memset(f1, 0, sizeof(dp[0]));
        f1[0][0] = 1;
        read(n, m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int x;
                read(x);
                swap(f0, f1);
                memset(f1, 0, sizeof(dp[0]));
                int need = ((1 << (m + 1)) - 1) ^ (1 << j) ^ (1 << (j + 1));
                for (int S = 0; S < (1 << (m + 1)); ++S)
                    for (int T = 0; T < (1 << (m + 1)); ++T)
                        if (f0[S][T])
                        {
                            for (int u = 0; u < 4; ++u)
                                for (int v = 0; v < 4; ++v)
                                {
                                    int cnt1 = (S >> j & 1) + (S >> (j + 1) & 1) + (u >> 1 & 1) + (u & 1);
                                    int cnt2 = (T >> j & 1) + (T >> (j + 1) & 1) + (v >> 1 & 1) + (v & 1);

                                    if ((x == -1 || cnt1 == x) && cnt1 == cnt2)
                                        add(f1[(S & need) | (u << j)][(T & need) | (v << j)], f0[S][T]);
                                }
                        }
            }
            swap(f0, f1);
            memset(f1, 0, sizeof(f1));
            for (int S = 0; S < (1 << m); ++S)
                for (int T = 0; T < (1 << m); ++T)
                    f1[S << 1][T << 1] = f0[S][T];
        }
        int res = f1[0][0];
        printf("%d\n", res);
    }
    return 0;
}