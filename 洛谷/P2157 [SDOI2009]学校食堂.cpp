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
inline void ckmin(int &x, int y)
{
    if (x > y)
        x = y;
}
const int N = 1005;
int n;
struct node
{
    int t, b;
} a[N];
int dp[N][(1 << 8) + 5][20];
inline void work()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i].t, a[i].b);
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0][7] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < (1 << 8); ++j)
            for (int k = -8; k <= 7; ++k)
            {
                if (dp[i][j][k + 8] == 0x3f3f3f3f)
                    continue;
                if ((j & 1))
                    ckmin(dp[i + 1][j >> 1][k + 7], dp[i][j][k + 8]);
                else
                    for (int l = 0, now = 0x3f3f3f3f; l < 8 && l <= now; ++l)
                    {
                        if (!((j >> l) & 1))
                        {
                            ckmin(dp[i][j | (1 << l)][l + 8], dp[i][j][k + 8] + (i + k ? (a[i + k].t ^ a[i + l].t) : 0));
                            now = min(now, l + a[i + l].b);
                        }
                    }
            }
    }
    int res = 0x3f3f3f3f;
    for (int i = 0; i <= 8; ++i)
        ckmin(res, dp[n + 1][0][i]);
    printf("%d\n", res);
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}