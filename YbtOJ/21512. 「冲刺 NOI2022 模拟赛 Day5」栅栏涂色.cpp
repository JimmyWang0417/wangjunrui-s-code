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
constexpr int N = 1e5 + 5, M = 5005;
int n, m;
int a[N];
int l[N], r[N];
int where[N];
int dp[M][M], cnt, sum[M];
inline int work()
{
    for (int i = 2; i <= cnt; ++i)
        sum[i] += sum[i - 1];
    for (int len = 1; len <= cnt; ++len)
        for (int i = 1; i + len - 1 <= cnt; ++i)
        {
            int j = i + len - 1;
            dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]) + sum[j] - sum[i - 1];
        }
    return dp[1][cnt];
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        if (!l[a[i]])
            where[l[a[i]] = i] = a[i];
        r[a[i]] = i;
    }
    ll answer = 0;
    for (int i = 1; i <= n; ++i)
        if (where[i])
        {
            cnt = 0;
            int x = i;
            while (where[x])
            {
                int &y = where[x];
                sum[++cnt] = r[y] - x + 1;
                x = r[y] + 1;
                y = 0;
            }
            answer += work();
        }
    printf("%lld\n", answer);
    return 0;
}
