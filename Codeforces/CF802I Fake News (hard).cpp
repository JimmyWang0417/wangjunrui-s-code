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
const int N = 2e5 + 5;
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
struct SAM
{
    int ch[26];
    int len, fa;
} point[N];
int dp[N];
int las = 1, tot = 1;
inline void insert(int c)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    dp[np] = 1;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
}
int n;
char str[N];
int nmsl[N], a[N];
inline void work()
{
    for (int i = 1; i <= tot; ++i)
        ++nmsl[point[i].len];
    for (int i = 1; i <= n; ++i)
        nmsl[i] += nmsl[i - 1];
    for (int i = tot; i >= 1; --i)
        a[nmsl[point[i].len]--] = i;
    ll ans = 0;
    for (int i = tot; i >= 1; --i)
    {
        int u = a[i];
        dp[point[u].fa] += dp[u];
        ans += (ll)(point[u].len - point[point[u].fa].len) * dp[u] * dp[u];
    }
    printf("%lld\n", ans);
}
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        scanf("%s", str);
        n = (int)strlen(str);
        for (int i = 0; str[i]; ++i)
            insert(str[i] - 'a');
        work();
        tot = las = 1;
        memset(point, 0, sizeof(point));
        memset(dp, 0, sizeof(dp));
        memset(nmsl, 0, sizeof(nmsl));
    }
    return 0;
}