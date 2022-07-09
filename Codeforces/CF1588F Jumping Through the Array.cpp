/**
 *    unicode: UTF-8
 *    name:    CF1588F Jumping Through the Array
 *    author:  wangjunrui
 *    created: 2022.07.08 周五 00:55:16 (Asia/Shanghai)
 **/
#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 2e5 + 5, M = 900 + 5;
int n, m;
int block;
ll a[N];
int from[N], to[N];
struct node
{
    int opt, x, y;
} b[N];
int belong[N], ed[N], color;
bool exist[N], vis[M];
int mp[N], tot;
int cnt[M];
int dp[M][M];
ll sum[N], add[M];
inline void dfs(int u)
{
    ed[belong[u] = ++color] = u;
    for (u = from[u]; !exist[u]; u = from[u])
        belong[u] = color;
}
inline void update(int u, int val)
{
    for (int v = belong[u]; !vis[v]; v = belong[to[ed[v]]])
    {
        add[v] += val;
        vis[v] = true;
    }
    memset(vis, 0, sizeof(vis));
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
    {
        read(to[i]);
        from[to[i]] = i;
    }
    read(m);
    for (int i = 1; i <= m; ++i)
        read(b[i].opt, b[i].x, b[i].y);
    block = (int)__builtin_sqrt(n);
    for (int l = 1, r; l <= m; l = r + 1)
    {
        r = min(m, l + block - 1);
        for (int i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + a[i];
        for (int i = l; i <= r; ++i)
            if (b[i].opt == 1)
            {
                if (!mp[b[i].x - 1] && b[i].x > 1)
                    mp[b[i].x - 1] = ++tot;
                if (!mp[b[i].y])
                    mp[b[i].y] = ++tot;
            }
            else if (b[i].opt == 2)
                exist[b[i].x] = true;
            else if (b[i].opt == 3)
            {
                exist[b[i].x] = true;
                exist[b[i].y] = true;
            }
        for (int i = 1; i <= n; ++i)
            if (exist[i])
                dfs(i);
        for (int i = 1; i <= n; ++i)
        {
            ++cnt[belong[i]];
            if (mp[i])
                memcpy(dp[mp[i]], cnt, sizeof(cnt));
        }
        for (int i = l; i <= r; ++i)
        {
            int opt = b[i].opt, x = b[i].x, y = b[i].y;
            if (opt == 1)
            {
                ll res = sum[y] - sum[x - 1];
                for (int j = 1; j <= color; ++j)
                    res += add[j] * (dp[mp[y]][j] - dp[mp[x - 1]][j]);
                printf("%lld\n", res);
            }
            else if (b[i].opt == 2)
                update(x, y);
            else
            {
                swap(to[x], to[y]);
                from[to[x]] = x;
                from[to[y]] = y;
            }
        }
        for (int i = 1; i <= n; ++i)
            a[i] += add[belong[i]];
        tot = color = 0;
        memset(mp, 0, sizeof(mp));
        memset(exist, 0, sizeof(exist));
        memset(cnt, 0, sizeof(cnt));
        memset(dp, 0, sizeof(dp));
        memset(add, 0, sizeof(add));
        memset(belong, 0, sizeof(belong));
    }
    return 0;
}