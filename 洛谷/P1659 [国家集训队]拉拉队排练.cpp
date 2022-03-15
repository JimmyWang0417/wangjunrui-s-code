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
const int N = 1e6 + 5, mod = 19930726;
inline ll quickpow(ll a, int b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Point
{
    int ch[26];
    int fa, len;
} point[N];
int tot = 1, las = 0;
char str[N];
int dp[N];
inline int getfa(int x, int where)
{
    while (str[where] != str[where - point[x].len - 1])
        x = point[x].fa;
    return x;
}
inline void insert(int c, int where)
{
    int cur = getfa(las, where);
    int now = point[cur].ch[c];
    if (!now)
    {
        now = ++tot;
        point[now].fa = point[getfa(point[cur].fa, where)].ch[c];
        point[now].len = point[cur].len + 2;
        point[cur].ch[c] = now;
    }
    ++dp[now];
    las = now;
}
int n;
ll k;
int nmsl[N];
int q[N];
inline void work()
{
    for (int i = 2; i <= tot; ++i)
        ++nmsl[point[i].len];
    for (int i = 2; i <= n; ++i)
        nmsl[i] += nmsl[i - 1];
    for (int i = tot; i >= 2; --i)
        q[nmsl[point[i].len]--] = i;
    ll ans = 1;
    for (int i = tot - 1; i >= 1 && k; --i)
    {
        int u = q[i];
        dp[point[u].fa] += dp[u];
        if (point[u].len & 1)
        {
            int res = (int)min(k, (ll)dp[u]);
            (ans *= quickpow(point[u].len, res)) %= mod;
            k -= res;
        }
    }
    if (k)
        printf("-1\n");
    else
        printf("%lld\n", ans);
}
signed main()
{
    point[0].fa = 1;
    point[1].len = -1;
    read(n, k);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
        insert(str[i] - 'a', i);
    work();
    return 0;
}