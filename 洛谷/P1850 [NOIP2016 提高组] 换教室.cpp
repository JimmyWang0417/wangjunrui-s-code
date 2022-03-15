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
const int N = 2005, M = 305;
int n, m, v, e;
struct node
{
    int c, d;
    double p;
} a[N];
double dp[N][N][2];
int dis[M][M];
signed main()
{
    memset(dis, 0x3f, sizeof(dis));
    read(n, m, v, e);
    for (int i = 1; i <= n; ++i)
        read(a[i].c);
    for (int i = 1; i <= n; ++i)
        read(a[i].d);
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &a[i].p);
    for (int i = 1; i <= e; ++i)
    {
        int x, y, z;
        read(x, y, z);
        dis[x][y] = dis[y][x] = min(dis[x][y], z);
    }
    for (int i = 1; i <= v; ++i)
        dis[i][i] = 0;
    for (int k = 1; k <= v; ++k)
        for (int i = 1; i <= v; ++i)
            for (int j = 1; j <= v; ++j)
                ckmin(dis[i][j], dis[i][k] + dis[k][j]);
    memset(dp, 0x48, sizeof(dp));
    dp[1][0][0] = dp[1][1][1] = 0;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j <= i && j <= m; ++j)
        {
            dp[i + 1][j][0] = min(dp[i][j][0] + dis[a[i].c][a[i + 1].c],
                                  dp[i][j][1] + a[i].p * dis[a[i].d][a[i + 1].c] + (1 - a[i].p) * dis[a[i].c][a[i + 1].c]);
            dp[i + 1][j + 1][1] = min(dp[i][j][0] + a[i + 1].p * dis[a[i].c][a[i + 1].d] + (1 - a[i + 1].p) * dis[a[i].c][a[i + 1].c],
                                      dp[i][j][1] + a[i].p * (a[i + 1].p * dis[a[i].d][a[i + 1].d] + (1 - a[i + 1].p) * dis[a[i].d][a[i + 1].c]) + (1 - a[i].p) * (a[i + 1].p * dis[a[i].c][a[i + 1].d] + (1 - a[i + 1].p) * dis[a[i].c][a[i + 1].c]));
        }
    double res = dp[0][0][0];
    for (int j = 0; j <= m; ++j)
        ckmin(res, min(dp[n][j][0], dp[n][j][1]));
    printf("%.2lf\n", res);
    return 0;
}