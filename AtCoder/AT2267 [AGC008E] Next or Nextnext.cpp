#include <cstdio>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(x) (x & (-x))
template <typename T>
inline void read(T &x)
{
    x = 0;
    char s = (char)getchar();
    bool dp = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            dp = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar();
    }
    if (dp)
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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
int n, a[N];
int deg[N];
int vis[N];
bool exist[N];
ll answer = 1;
int foot[N];
int cnt[N];
inline void solve(int x)
{
    int now = 0, fir = 0, las = 0, firl = 0;
    while (exist[x])
    {
        ++now;
        exist[x] = false;
        if (foot[x])
        {
            if (fir)
            {
                (answer *= (foot[x] < now - las) + (foot[x] <= now - las)) %= mod;
                las = now;
            }
            else
            {
                fir = las = now;
                firl = foot[x];
            }
        }
        x = a[x];
    }
    if (fir)
        (answer *= (firl < now - las + fir) + (firl <= now - las + fir)) %= mod;
    else
        ++cnt[now];
}
ll dp[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        ++deg[a[i]];
    }
    for (int i = 1; i <= n; ++i)
    {
        if (vis[i])
            continue;
        int x = i;
        while (!vis[x])
        {
            vis[x] = i;
            x = a[x];
        }
        if (vis[x] == i)
            while (!exist[x])
            {
                exist[x] = true;
                x = a[x];
            }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (exist[i] && deg[i] > 2)
        {
            printf("0\n");
            return 0;
        }
        if (!exist[i] && deg[i] > 1)
        {
            printf("0\n");
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (deg[i])
            continue;
        int x = i, len = 0;
        while (!exist[x])
        {
            ++len;
            x = a[x];
        }
        foot[x] = len;
    }
    for (int i = 1; i <= n; ++i)
        if (exist[i])
            solve(i);
    for (int i = 1; i <= n; ++i)
    {
        dp[0] = 1;
        for (int j = 1; j <= cnt[i]; ++j)
        {
            if (i > 1 && (i & 1))
                dp[j] = (dp[j - 1] + dp[j - 1]) % mod; //情况1,2
            else
                dp[j] = dp[j - 1]; //情况1
            if (j > 1)
                (dp[j] += 1LL * dp[j - 2] * (j - 1) % mod * i) %= mod; //情况3
        }
        (answer *= dp[cnt[i]]) %= mod;
    }
    printf("%lld\n", answer);
    return 0;
}