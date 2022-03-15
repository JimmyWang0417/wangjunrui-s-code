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
const int N = 80, M = 2105;
int n;
int dp[2][M][M];
struct node
{
    int h, t;
    inline bool operator<(const node &rhs) const
    {
        return h == rhs.h ? t > rhs.t : h > rhs.h;
    }
} a[N];
int sum[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i].h, a[i].t);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + a[i].t;
    int now = 0, nxt = 1;
    memset(dp[now], 0x3f, sizeof(dp[now]));
    dp[now][0][0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        memset(dp[nxt], 0x3f, sizeof(dp[nxt]));
        for (int j = 0; j <= sum[i - 1]; ++j)
            for (int k = 0; k <= sum[i - 1] - j; ++k)
                if (dp[now][j][k] != 0x3f3f3f3f)
                {
                    ckmin(dp[nxt][j][k], dp[now][j][k]);
                    ckmin(dp[nxt][j + a[i].t][k], dp[now][j][k] + (j ? 0 : a[i].h));
                    ckmin(dp[nxt][j][k + a[i].t], dp[now][j][k] + (k ? 0 : a[i].h));
                }
        swap(now, nxt);
    }
    int res = 0x3f3f3f3f;
    for (int i = 0; i <= sum[n]; ++i)
        for (int j = 0; j <= sum[n] - i; ++j)
            if (dp[now][i][j] != 0x3f3f3f3f && i && j && sum[n] - i - j)
                ckmin(res, (dp[now][i][j] + a[1].h) * max(max(i, j), sum[n] - i - j));
    printf("%d\n", res);
    return 0;
}