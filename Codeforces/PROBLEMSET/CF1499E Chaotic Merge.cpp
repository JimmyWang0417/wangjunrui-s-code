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
const int N = 1005;
const int mod = 998244353;
int n, m;
char S[N], T[N];
int dp[N][N][2][4];
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
signed main()
{
    scanf("%s%s", S + 1, T + 1);
    n = (int)strlen(S + 1), m = (int)strlen(T + 1);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
        {
            if (i < n)
                add(dp[i + 1][j][0][1], 1);
            if (j < m)
                add(dp[i][j + 1][1][2], 1);
            for (int s = 0; s < 4; ++s)
            {
                if (i < n)
                {
                    if (S[i + 1] != S[i])
                        add(dp[i + 1][j][0][s | 1], dp[i][j][0][s]);
                    if (S[i + 1] != T[j])
                        add(dp[i + 1][j][0][s | 1], dp[i][j][1][s]);
                }
                if (j < m)
                {
                    if (T[j + 1] != S[i])
                        add(dp[i][j + 1][1][s | 2], dp[i][j][0][s]);
                    if (T[j + 1] != T[j])
                        add(dp[i][j + 1][1][s | 2], dp[i][j][1][s]);
                }
            }
        }
    int res = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            add(res, dp[i][j][0][3]);
            add(res, dp[i][j][1][3]);
        }
    printf("%d\n", res);
    return 0;
}