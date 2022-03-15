#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 5e5 + 5, K = 35;
constexpr int mod = 998244353;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void dec(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n, k, m;
struct node
{
    int l, r, x;
} a[N];
int diff[N];
ll answer = 1;
int pos[N];
int dp[N];
inline void solve(int x)
{
    memset(pos, 0, sizeof(pos));
    memset(diff, 0, sizeof(diff));
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; ++i)
        if ((a[i].x >> x) & 1)
        {
            ++diff[a[i].l];
            --diff[a[i].r + 1];
        }
        else
            ckmax(pos[a[i].r + 1], a[i].l);
    for (int i = 2; i <= n + 1; ++i)
    {
        diff[i] += diff[i - 1];
        ckmax(pos[i], pos[i - 1]);
    }
    dp[0] = 1;
    int l = 0, sum = 1;
    for (int i = 1; i <= n + 1; ++i)
    {
        while (l < pos[i])
            dec(sum, dp[l++]);
        if (!diff[i])
        {
            dp[i] = sum;
            add(sum, sum);
        }
    }
    (answer *= dp[n + 1]) %= mod;
}
signed main()
{
    read(n, k, m);
    for (int i = 1; i <= m; ++i)
        read(a[i].l, a[i].r, a[i].x);
    for (int i = k - 1; i >= 0; --i)
        solve(i);
    printf("%lld\n", answer);
    return 0;
}