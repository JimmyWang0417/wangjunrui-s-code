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
const int N = 105;
const int mod = 9999973;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m;
int dp[N][N][N];
signed main()
{
    read(n, m);
    dp[0][0][0] = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k + j <= m; ++k)
                if (dp[i][j][k])
                {
#define las dp[i][j][k]
                    add(dp[i + 1][j][k], las);
                    add(dp[i + 1][j + 1][k], (int)((ll)las * (m - j - k) % mod));
                    if (j >= 1)
                        add(dp[i + 1][j - 1][k + 1], (int)((ll)las * j % mod));
                    add(dp[i + 1][j + 2][k], (int)((ll)las * (m - j - k) * (m - j - k - 1) / 2 % mod));
                    add(dp[i + 1][j][k + 1], (int)((ll)las * (m - j - k) * j % mod));
                    if (j >= 2)
                        add(dp[i + 1][j - 2][k + 2], (int)((ll)las * j * (j - 1) / 2 % mod));
                }
    //	for(int i=1; i<=n; ++i)
    //		for(int j=0; j<=m; ++j)
    //			for(int k=0; k<=m; ++k)
    //				if(dp[i][j][k])
    //					printf("dp[%lld][%lld][%lld]=%lld\n",i,j,k,dp[i][j][k]);
    int ans = 0;
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= m; ++j)
            add(ans, dp[n][i][j]);
    printf("%d\n", ans);
    return 0;
}
