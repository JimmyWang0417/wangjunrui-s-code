#include <bits/stdc++.h>
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
constexpr int N = 2e5 + 5;
int n, m;
vector<int> g[N], h[N], que;
int deg[N];
int dp[2][N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        h[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
    {
        deg[i] = (int)h[i].size();
        if (!deg[i])
            que.push_back(i);
    }
    for (int i = 0; i < (int)que.size(); ++i)
        for (auto v : g[que[i]])
            if (!--deg[v])
                que.push_back(v);
    if ((int)que.size() < n)
    {
        puts("-1");
        return 0;
    }
    iota(dp[0] + 1, dp[0] + 1 + n, 1);
    for (int i = 0; i < n; ++i)
        for (auto v : h[que[i]])
            ckmin(dp[0][que[i]], dp[0][v]);
    iota(dp[1] + 1, dp[1] + 1 + n, 1);
    for (int i = n - 1; i >= 0; --i)
        for (auto v : g[que[i]])
            ckmin(dp[1][que[i]], dp[1][v]);
    int res = 0;
    for (int i = 1; i <= n; ++i)
        if (dp[0][i] >= i && dp[1][i] >= i)
            ++res;
    printf("%d\n", res);
    for (int i = 1; i <= n; ++i)
        putchar("EA"[dp[0][i] >= i && dp[1][i] >= i]);
    putchar('\n');
    return 0;
}