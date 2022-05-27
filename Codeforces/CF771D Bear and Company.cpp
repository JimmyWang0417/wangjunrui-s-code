// Problem: D. Bear and Company
// Contest: Codeforces - VK Cup 2017 - Round 1
// URL: https://codeforces.com/problemset/problem/771/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 80;
int n;
char str[N];
int dp[N][N][N][3];
int posv[N], posk[N], posc[N];
int cntv, cntk, cntc;
int g[3][N][N];
signed main()
{
    read(n);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
        switch (str[i])
        {
        case 'V':
            posv[++cntv] = i;
            break;
        case 'K':
            posk[++cntk] = i;
            break;
        default:
            posc[++cntc] = i;
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= cntv; ++j)
            g[0][i][j] = g[0][i][j - 1] + (posv[j] > i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= cntk; ++j)
            g[1][i][j] = g[1][i][j - 1] + (posk[j] > i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= cntc; ++j)
            g[2][i][j] = g[2][i][j - 1] + (posc[j] > i);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][2] = 0;
    for (int i = 0; i <= cntv; ++i)
        for (int j = 0; j <= cntk; ++j)
            for (int k = 0; k <= cntc; ++k)
                for (int t = 0; t < 3; ++t)
                {
                    if (i < cntv)
                        ckmin(dp[i + 1][j][k][0], dp[i][j][k][t] + g[1][posv[i + 1]][j] + g[2][posv[i + 1]][k]);
                    if (j < cntk && t != 0)
                        ckmin(dp[i][j + 1][k][1], dp[i][j][k][t] + g[0][posk[j + 1]][i] + g[2][posk[j + 1]][k]);
                    if (k < cntc)
                        ckmin(dp[i][j][k + 1][2], dp[i][j][k][t] + g[0][posc[k + 1]][i] + g[1][posc[k + 1]][j]);
                }
    int res = INT_MAX;
    for (int t = 0; t < 3; ++t)
        ckmin(res, dp[cntv][cntk][cntc][t]);
    printf("%d\n", res);
    return 0;
}