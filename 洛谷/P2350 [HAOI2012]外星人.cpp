#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
using namespace std;
const int N = 1e5 + 5;
int prime[N], tot;
int dp[N];
bool vis[N];
inline void getprime(int n)
{
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            dp[i] = dp[i - 1];
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            dp[i * prime[j]] = dp[i] + dp[prime[j]];
            if (i % prime[j] == 0)
                break;
        }
    }
}
inline void work()
{
    int n;
    read(n);
    bool flag = false;
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int p, q;
        read(p, q);
        ans += (ll)dp[p] * q;
        if (p == 2)
            flag = true;
    }
    if (!flag)
        ++ans;
    printf("%lld\n", ans);
}
signed main()
{
    getprime(1e5);
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}