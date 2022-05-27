#include <bits/extc++.h>
#include <bits/stdc++.h>
#define ll long long
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
const int N = 3.5e4 + 5, K = 105;
int n, m, a[N];
int lft[N], rgh[N], mp[N];
ll dp[N][K];
int cnt[N];
inline ll calc(int ql, int qr)
{
    static int l = 1, r = 0;
    static ll answer = 0;
    while (ql < l)
    {
        --l;
        ++cnt[a[l]];
        if (cnt[a[l]] > 1)
            answer += rgh[l];
    }
    while (qr > r)
    {
        ++r;
        ++cnt[a[r]];
        if (cnt[a[r]] > 1)
            answer += lft[r];
    }
    while (ql > l)
    {
        if (cnt[a[l]] > 1)
            answer -= rgh[l];
        --cnt[a[l]];
        ++l;
    }
    while (qr < r)
    {
        if (cnt[a[r]] > 1)
            answer -= lft[r];
        --cnt[a[r]];
        --r;
    }
    return answer;
}
inline void solve(int k, int l, int r, int L, int R)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    int maxx = min(R, mid - 1);
    ll &ans = dp[mid][k];
    int where = maxx;
    for (int i = L; i <= maxx; ++i)
    {
        ll res = dp[i][k - 1] + calc(i + 1, mid);
        if (ans > res)
        {
            ans = res;
            where = i;
        }
    }
    solve(k, l, mid - 1, L, where), solve(k, mid + 1, r, where, R);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
    {
        lft[i] = mp[a[i]] ? i - mp[a[i]] : 0;
        mp[a[i]] = i;
    }
    memset(mp, 0, sizeof(mp));
    for (int i = n; i >= 1; --i)
    {
        rgh[i] = mp[a[i]] ? mp[a[i]] - i : 0;
        mp[a[i]] = i;
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= m; ++i)
        solve(i, 0, n, 0, n);
    printf("%lld\n", dp[n][m]);
    return 0;
}