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
constexpr int N = 3005;
int n, m;
vector<int> a[N];
ll sum[N];
ll f[15][N], dp[N], answer;
inline void dfs(int l, int r, int dep)
{
    if (l == r)
    {
        ll now = 0;
        for (int i = 0; i <= m && i <= (int)a[l].size(); ++i)
        {
            ckmax(dp[m], now + dp[m - i]);
            if (i < (int)a[l].size())
                now += a[l][i];
        }
        ckmax(answer, dp[m]);
        return;
    }
    int mid = (l + r) >> 1;
    memcpy(f[dep], dp, sizeof(dp));
    for (int i = mid + 1; i <= r; ++i)
        for (int j = m; j >= (int)a[i].size(); --j)
            ckmax(dp[j], dp[j - (int)a[i].size()] + sum[i]);
    dfs(l, mid, dep + 1);
    memcpy(dp, f[dep], sizeof(dp));
    for (int i = l; i <= mid; ++i)
        for (int j = m; j >= (int)a[i].size(); --j)
            ckmax(dp[j], dp[j - (int)a[i].size()] + sum[i]);
    dfs(mid + 1, r, dep + 1);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int cnt, x;
        read(cnt);
        while (cnt--)
        {
            read(x);
            a[i].push_back(x);
            sum[i] += x;
        }
    }
    dfs(1, n, 0);
    printf("%lld\n", answer);
    return 0;
}