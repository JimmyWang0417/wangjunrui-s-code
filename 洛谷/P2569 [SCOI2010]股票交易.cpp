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
const int N = 2005;
inline void ckmax(int &x, int y)
{
    if (x < y)
        x = y;
}
int dp[N][N];
int q[N], head, tail;
int T, maxP, W;
signed main()
{
    read(T, maxP, W);
    memset(dp[0], ~0x3f, sizeof(dp[0]));
    dp[0][0] = 0;
    for (int i = 1; i <= T; ++i)
    {
        memcpy(dp[i], dp[i - 1], sizeof(dp[i]));
        int ap, bp, as, bs;
        read(ap, bp, as, bs);
        for (int j = 1; j <= as; ++j)
            ckmax(dp[i][j], -ap * j);
        int las = i - W - 1;
        if (las > 0)
        {
            head = tail = 1;
            q[1] = 0;
#define g(x) (dp[las][x] + x * ap)
            for (int j = 1; j <= maxP; ++j)
            {
                while (head <= tail && q[head] < j - as)
                    ++head;
                ckmax(dp[i][j], dp[las][q[head]] - (j - q[head]) * ap);
                while (head <= tail && g(q[tail]) < g(j))
                    --tail;
                q[++tail] = j;
            }
#undef g
#define g(x) (dp[las][x] + x * bp)
            head = tail = 1;
            q[1] = maxP;
            for (int j = maxP - 1; j >= 0; --j)
            {
                while (head <= tail && q[head] > j + bs)
                    ++head;
                ckmax(dp[i][j], dp[las][q[head]] + (q[head] - j) * bp);
                while (head <= tail && g(q[tail]) < g(j))
                    --tail;
                q[++tail] = j;
            }
#undef g
        }
    }
    printf("%d\n", dp[T][0]);
    return 0;
}