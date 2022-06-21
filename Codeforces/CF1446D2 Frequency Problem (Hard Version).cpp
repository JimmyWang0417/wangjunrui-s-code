#include <algorithm>
#include <climits>
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
constexpr int N = 2e5 + 5;
int n, a[N];
vector<int> g[N];
int where;
int lef[N], rig[N];
int pre[N];
bool vis[N];
int las[N], nxt[N];
int dp[N * 2];
int p[N], tot;
int b[N], c[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (!g[a[i]].empty())
        {
            c[g[a[i]].back()] = i;
            b[i] = g[a[i]].back();
        }
        g[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i)
        if (!c[i])
            c[i] = n + 1;
    for (int i = 1; i <= n; ++i)
        if (g[i].size() > g[where].size())
            where = i;
    for (int i = 1; i <= n; ++i)
        if (a[i] == where)
        {
            pre[i] = pre[i - 1] + 1;
            las[i] = i;
        }
        else
        {
            pre[i] = pre[i - 1];
            las[i] = las[i - 1];
        }
    nxt[n + 1] = n + 1;
    for (int i = n; i >= 1; --i)
        if (a[i] == where)
            nxt[i] = i;
        else
            nxt[i] = nxt[i + 1];
    memset(dp, ~0x3f, sizeof(dp));
    int res = 0;
    for (int col = 1; col <= n; ++col)
    {
        if (where == col || g[col].empty())
            continue;
        int maxx = INT_MIN;
        for (int i = 0; i < (int)g[col].size(); ++i)
        {
            ckmax(maxx, pre[g[col][i]] - i);
            rig[g[col][i]] = (i + 1) - pre[g[col][i]] + maxx;
        }
        maxx = INT_MIN;
        for (int i = (int)g[col].size() - 1; i >= 0; --i)
        {
            ckmax(maxx, (i + 1) - pre[g[col][i]]);
            lef[g[col][i]] = maxx - i + pre[g[col][i]];
        }
        tot = 0;
        for (auto u : g[col])
        {
            int beg = tot;
            for (int T = lef[u], i = las[u]; T-- && !vis[i] && i > b[u]; i = b[i])
            {
                vis[p[++tot] = i] = true;
            }
            reverse(p + beg + 1, p + 1 + tot);
            p[++tot] = u;
            for (int T = rig[u], i = nxt[u]; T-- && !vis[i] && i < c[u]; i = c[i])
                vis[p[++tot] = i] = true;
        }
        p[tot + 1] = n + 1;
        for (int i = 1, now = 0; i <= tot; ++i)
        {
            int u = p[i];
            ckmax(dp[now - pre[u - 1] + n], -max(p[i - 1], las[u - 1]));
            if (a[u] == col)
                ++now;
            ckmax(res, dp[now - pre[u] + n] + min(p[i + 1], nxt[u + 1]) - 1);
        }
        for (int i = 1, now = 0; i <= tot; ++i)
        {
            int u = p[i];
            dp[now - pre[u - 1] + n] = ~0x3f3f3f3f;
            vis[u] = false;
            if (a[u] == col)
                ++now;
        }
    }
    printf("%d\n", res);
    return 0;
}