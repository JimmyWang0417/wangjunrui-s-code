#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
using namespace std;
const int N = 20, mod = 1e9 + 7;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, cnt[N];
ll dp[N][N][N][N][N][5];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        ++cnt[x];
    }
    if (cnt[1])
        dp[cnt[1] - 1][cnt[2]][cnt[3]][cnt[4]][cnt[5]][0] = cnt[1];
    if (cnt[2])
        dp[cnt[1] + 1][cnt[2] - 1][cnt[3]][cnt[4]][cnt[5]][1] = cnt[2];
    if (cnt[3])
        dp[cnt[1]][cnt[2] + 1][cnt[3] - 1][cnt[4]][cnt[5]][2] = cnt[3];
    if (cnt[4])
        dp[cnt[1]][cnt[2]][cnt[3] + 1][cnt[4] - 1][cnt[5]][3] = cnt[4];
    if (cnt[5])
        dp[cnt[1]][cnt[2]][cnt[3]][cnt[4] + 1][cnt[5] - 1][4] = cnt[5];
    for (int e = cnt[5]; e >= 0; --e)
        for (int d = cnt[4] + cnt[5]; d >= 0; --d)
            if (d + e <= n)
                for (int c = cnt[3] + cnt[4] + cnt[5]; c >= 0; --c)
                    if (c + d + e <= n)
                        for (int b = cnt[2] + cnt[3] + cnt[4] + cnt[5]; b >= 0; --b)
                            if (b + c + d + e <= n)
                                for (int a = n; a >= 0; --a)
                                    if (a + b + c + d + e <= n)
                                    {
                                        if (!a && !b && !c && !d && !e)
                                            continue;
                                        if (dp[a][b][c][d][e][0])
                                        {
                                            if (a)
                                                add(dp[a - 1][b][c][d][e][0], dp[a][b][c][d][e][0] * a % mod);
                                            if (b)
                                                add(dp[a + 1][b - 1][c][d][e][1], dp[a][b][c][d][e][0] * b % mod);
                                            if (c)
                                                add(dp[a][b + 1][c - 1][d][e][2], dp[a][b][c][d][e][0] * c % mod);
                                            if (d)
                                                add(dp[a][b][c + 1][d - 1][e][3], dp[a][b][c][d][e][0] * d % mod);
                                            if (e)
                                                add(dp[a][b][c][d + 1][e - 1][4], dp[a][b][c][d][e][0] * e % mod);
                                        }
                                        if (dp[a][b][c][d][e][1])
                                        {
                                            if (a)
                                                add(dp[a - 1][b][c][d][e][0], dp[a][b][c][d][e][1] * (a - 1) % mod);
                                            if (b)
                                                add(dp[a + 1][b - 1][c][d][e][1], dp[a][b][c][d][e][1] * b % mod);
                                            if (c)
                                                add(dp[a][b + 1][c - 1][d][e][2], dp[a][b][c][d][e][1] * c % mod);
                                            if (d)
                                                add(dp[a][b][c + 1][d - 1][e][3], dp[a][b][c][d][e][1] * d % mod);
                                            if (e)
                                                add(dp[a][b][c][d + 1][e - 1][4], dp[a][b][c][d][e][1] * e % mod);
                                        }
                                        if (dp[a][b][c][d][e][2])
                                        {
                                            if (a)
                                                add(dp[a - 1][b][c][d][e][0], dp[a][b][c][d][e][2] * a % mod);
                                            if (b)
                                                add(dp[a + 1][b - 1][c][d][e][1], dp[a][b][c][d][e][2] * (b - 1) % mod);
                                            if (c)
                                                add(dp[a][b + 1][c - 1][d][e][2], dp[a][b][c][d][e][2] * c % mod);
                                            if (d)
                                                add(dp[a][b][c + 1][d - 1][e][3], dp[a][b][c][d][e][2] * d % mod);
                                            if (e)
                                                add(dp[a][b][c][d + 1][e - 1][4], dp[a][b][c][d][e][2] * e % mod);
                                        }

                                        if (dp[a][b][c][d][e][3])
                                        {
                                            if (a)
                                                add(dp[a - 1][b][c][d][e][0], dp[a][b][c][d][e][3] * a % mod);
                                            if (b)
                                                add(dp[a + 1][b - 1][c][d][e][1], dp[a][b][c][d][e][3] * b % mod);
                                            if (c)
                                                add(dp[a][b + 1][c - 1][d][e][2], dp[a][b][c][d][e][3] * (c - 1) % mod);
                                            if (d)
                                                add(dp[a][b][c + 1][d - 1][e][3], dp[a][b][c][d][e][3] * d % mod);
                                            if (e)
                                                add(dp[a][b][c][d + 1][e - 1][4], dp[a][b][c][d][e][3] * e % mod);
                                        }
                                        if (dp[a][b][c][d][e][4])
                                        {
                                            if (a)
                                                add(dp[a - 1][b][c][d][e][0], dp[a][b][c][d][e][4] * a % mod);
                                            if (b)
                                                add(dp[a + 1][b - 1][c][d][e][1], dp[a][b][c][d][e][4] * b % mod);
                                            if (c)
                                                add(dp[a][b + 1][c - 1][d][e][2], dp[a][b][c][d][e][4] * c % mod);
                                            if (d)
                                                add(dp[a][b][c + 1][d - 1][e][3], dp[a][b][c][d][e][4] * (d - 1) % mod);
                                            if (e)
                                                add(dp[a][b][c][d + 1][e - 1][4], dp[a][b][c][d][e][4] * e % mod);
                                        }
                                    }
    printf("%lld\n", max(max(max(dp[0][0][0][0][0][0], dp[0][0][0][0][0][1]),
                             max(dp[0][0][0][0][0][2], dp[0][0][0][0][0][3])),
                         dp[0][0][0][0][0][4]));
    return 0;
}