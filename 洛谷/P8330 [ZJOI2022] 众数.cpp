#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
#define lll __int128
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
constexpr int N = 2e5 + 5, M = 455;
int n, a[N];
int p[N], tot;
int dp[N][M];
int pre[N];
int answer[N];
vector<int> g[N];
inline void work()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[++tot] = a[i];
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    for (int i = 1; i <= n; ++i)
        g[a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p)].push_back(i);
    int block = (int)sqrt(n);
    memset(dp, 0x3f, sizeof(dp));
    for (int kase = 1; kase <= tot; ++kase)
        if ((int)g[kase].size() <= block)
        {
            for (int j = 1; j <= block; ++j)
                for (int i = 0; i + j <= (int)g[kase].size(); ++i)
                    ckmin(dp[g[kase][i]][j], g[kase][i + j - 1]);
        }
        else
        {
            for (auto u : g[kase])
                pre[u] = 1;
            for (int i = 2; i <= n; ++i)
                pre[i] += pre[i - 1];
            for (int color = 1; color <= tot; ++color)
            {
                if (color == kase)
                    continue;
                int maxx = 0;
                for (int i = 0; i < (int)g[color].size(); ++i)
                {
                    ckmax(answer[color], (int)g[color].size() - i + pre[g[color][i]] + maxx);
                    ckmax(maxx, i + 1 - pre[g[color][i]]);
                }
                ckmax(answer[color], pre[n] + maxx);
            }
            fill(pre + 1, pre + 1 + n, 0);
        }
    for (int j = 1; j <= block; ++j)
        for (int i = n - j; i >= 1; --i)
            ckmin(dp[i][j], dp[i + 1][j]);
    for (int kase = 1; kase <= tot; ++kase)
    {
        ckmax(answer[kase], (int)g[kase].size());
        for (int add = 1; add <= block && dp[1][add] <= n; ++add)
        {
            int j = 0;
            while (j < (int)g[kase].size() && dp[1][add] >= g[kase][j])
                ++j;
            ckmax(answer[kase], (int)g[kase].size() - j + add);
            for (int i = 0; i < (int)g[kase].size() && dp[g[kase][i] + 1][add] <= n; ++i)
            {
                while (j < (int)g[kase].size() && dp[g[kase][i] + 1][add] >= g[kase][j])
                    ++j;
                ckmax(answer[kase], i + 1 + (int)g[kase].size() - j + add);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= tot; ++i)
        ckmax(res, answer[i]);
    printf("%d\n", res);
    for (int i = 1; i <= tot; ++i)
        if (res == answer[i])
            printf("%d\n", p[i]);
    for (int i = 1; i <= tot; ++i)
    {
        answer[i] = 0;
        g[i].clear();
    }
}
signed main()
{
    int T = 1;
    read(T);
    while (T--)
        work();
    return 0;
}