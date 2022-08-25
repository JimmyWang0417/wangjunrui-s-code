/**
 *    unicode: UTF-8
 *    name:    P8294 [省选联考 2022] 最大权独立集问题
 *    author:  wangjunrui
 *    created: 2022.08.23 周二 22:35:28 (Asia/Shanghai)
 **/
#include <bitset>
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
constexpr int N = 5005;
int n;
int a[N];
int fa[N], lc[N], rc[N];
ll dp[4][N][N];
bitset<N> status[N];
vector<int> g[N];
inline ll calc(int x, int y, int z)
{
    if (x == y)
        return dp[0][x][z];
    else if (!rc[x])
        return dp[1][lc[x]][y] + a[y] + a[z];
    else if (status[lc[x]][y])
        return min(dp[1][lc[x]][y] + dp[2][rc[x]][z], dp[3][x][y]) + a[y] + a[z];
    else
        return min(dp[1][rc[x]][y] + dp[2][lc[x]][z], dp[3][x][y]) + a[y] + a[z];
}
signed main()
{
    read(n);
    for (int u = 1; u <= n; ++u)
        read(a[u]);
    for (int u = 2; u <= n; ++u)
    {
        read(fa[u]);
        if (!lc[fa[u]])
            lc[fa[u]] = u;
        else
            rc[fa[u]] = u;
    }
    for (int u = n; u > 1; --u)
    {
        g[u].push_back(u);
        status[u].set(u);

        // dp0
        if (!lc[u])
        {
            for (int v = 1; v <= n; ++v)
                if (!status[u][v])
                    dp[0][u][v] = a[u] + a[v];
        }
        else if (!rc[u])
        {
            for (int v = 1; v <= n; ++v)
                if (!status[u][v])
                    dp[0][u][v] = a[u] + a[v] + dp[2][lc[u]][v];
        }
        else
        {
            ll min1 = 1e18, min2 = 1e18, min3 = 1e18;
            for (int v = 1; v <= n; ++v)
                if (!status[u][v])
                    dp[0][u][v] = 1e18;
            for (int x : g[lc[u]])
            {
                ll minn = 1e18;
                for (int y : g[rc[u]])
                    ckmin(minn, calc(rc[u], y, x));
                if (x == lc[u])
                {
                    for (int v = 1; v <= n; ++v)
                        if (!status[u][v])
                            ckmin(dp[0][u][v], a[u] + a[v] + calc(lc[u], x, v) + minn);
                    continue;
                }

                if (!rc[lc[u]])
                    ckmin(min1, minn + a[u] + dp[1][lc[lc[u]]][x] + a[x]);
                else
                {
                    if (status[lc[lc[u]]][x])
                    {
                        ckmin(min2, dp[1][lc[lc[u]]][x] + a[x] + minn + a[u]);
                        ckmin(min1, a[x] + minn + a[u] + dp[3][lc[u]][x]);
                    }
                    else
                    {
                        ckmin(min3, dp[1][rc[lc[u]]][x] + a[x] + minn + a[u]);
                        ckmin(min1, a[x] + minn + a[u] + dp[3][lc[u]][x]);
                    }
                }
            }

            if (!rc[lc[u]])
            {
                for (int v = 1; v <= n; ++v)
                    if (!status[u][v])
                        ckmin(dp[0][u][v], min1 + a[v] + a[v]);
            }
            else
            {
                for (int v = 1; v <= n; ++v)
                    if (!status[u][v])
                    {
                        ckmin(dp[0][u][v], min1 + a[v] + a[v]);
                        ckmin(dp[0][u][v], min2 + dp[2][rc[lc[u]]][v] + a[v] + a[v]);
                        ckmin(dp[0][u][v], min3 + dp[2][lc[lc[u]]][v] + a[v] + a[v]);
                    }
            }

            swap(lc[u], rc[u]);

            min1 = 1e18, min2 = 1e18, min3 = 1e18;
            for (int x : g[lc[u]])
            {
                ll minn = 1e18;
                for (int y : g[rc[u]])
                    ckmin(minn, calc(rc[u], y, x));
                if (x == lc[u])
                {
                    for (int v = 1; v <= n; ++v)
                        if (!status[u][v])
                            ckmin(dp[0][u][v], a[u] + a[v] + calc(lc[u], x, v) + minn);
                    continue;
                }

                if (!rc[lc[u]])
                    ckmin(min1, minn + a[u] + dp[1][lc[lc[u]]][x] + a[x]);
                else
                {
                    if (status[lc[lc[u]]][x])
                    {
                        ckmin(min2, dp[1][lc[lc[u]]][x] + a[x] + minn + a[u]);
                        ckmin(min1, a[x] + minn + a[u] + dp[3][lc[u]][x]);
                    }
                    else
                    {
                        ckmin(min3, dp[1][rc[lc[u]]][x] + a[x] + minn + a[u]);
                        ckmin(min1, a[x] + minn + a[u] + dp[3][lc[u]][x]);
                    }
                }
            }

            if (!rc[lc[u]])
            {
                for (int v = 1; v <= n; ++v)
                    if (!status[u][v])
                        ckmin(dp[0][u][v], min1 + a[v] + a[v]);
            }
            else
            {
                for (int v = 1; v <= n; ++v)
                    if (!status[u][v])
                    {
                        ckmin(dp[0][u][v], min1 + a[v] + a[v]);
                        ckmin(dp[0][u][v], min2 + dp[2][rc[lc[u]]][v] + a[v] + a[v]);
                        ckmin(dp[0][u][v], min3 + dp[2][lc[lc[u]]][v] + a[v] + a[v]);
                    }
            }
        }

        // dp3
        if (rc[u])
        {
            for (int x : g[lc[u]])
                dp[3][u][x] = 1e18;
            for (int y : g[rc[u]])
                dp[3][u][y] = 1e18;
            for (int x : g[lc[u]])
                for (int y : g[rc[u]])
                {
                    ckmin(dp[3][u][x], calc(rc[u], y, u) + calc(lc[u], x, y));
                    ckmin(dp[3][u][y], calc(lc[u], x, u) + calc(rc[u], y, x));
                }
        }

        // dp1
        for (int v : g[u])
            dp[1][u][v] = calc(u, v, fa[u]);

        // dp2
        for (int v = 1; v <= n; ++v)
            if (!status[u][v])
                dp[2][u][v] = calc(u, u, v);

        if (!rc[u])
        {
            ll minn = 1e18;
            for (int v : g[lc[u]])
                ckmin(minn, a[v] + dp[1][lc[u]][v]);
            for (int v = 1; v <= n; ++v)
                if (!status[u][v])
                    ckmin(dp[2][u][v], minn + a[v]);
        }
        else
        {
            ll min1 = 1e18, min2 = 1e18, min3 = 1e18;
            for (int v : g[lc[u]])
            {
                ckmin(min1, dp[1][lc[u]][v] + a[v]);
                ckmin(min3, dp[3][u][v] + a[v]);
            }
            for (int v : g[rc[u]])
            {
                ckmin(min2, dp[1][rc[u]][v] + a[v]);
                ckmin(min3, dp[3][u][v] + a[v]);
            }
            for (int v = 1; v <= n; ++v)
                if (!status[u][v])
                {
                    ckmin(dp[2][u][v], min1 + dp[2][rc[u]][v] + a[v]);
                    ckmin(dp[2][u][v], min2 + dp[2][lc[u]][v] + a[v]);
                    ckmin(dp[2][u][v], min3 + a[v]);
                }
        }

        status[fa[u]] |= status[u];
        for (int v : g[u])
            g[fa[u]].push_back(v);
    }

    ll res = 1e18;
    if (!rc[1])
    {
        for (int i = 2; i <= n; i++)
            ckmin(res, calc(lc[1], i, 1));
    }
    else
    {
        for (int i : g[lc[1]])
            for (int j : g[rc[1]])
            {
                ckmin(res, calc(lc[1], i, 1) + calc(rc[1], j, i));
                ckmin(res, calc(rc[1], j, 1) + calc(lc[1], i, j));
            }
    }
    printf("%lld\n", res);
    return 0;
}