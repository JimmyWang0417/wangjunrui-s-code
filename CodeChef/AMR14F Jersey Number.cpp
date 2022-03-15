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
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
constexpr int inv4 = (mod + 1) / 4;
constexpr int m = 1 << 16;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
template <typename T>
inline void dec(T &x, T y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
inline int calc(char c)
{
    return '0' <= c && c <= '9' ? c - '0' : c - 'A' + 10;
}
int n;
char str[N];
int nxt[N][20];
pair<int, int> p[N];
int tot;
int dp[N], f[N];
inline void work()
{
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    for (int i = 0; i < 16; ++i)
        nxt[n + 1][i] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        int x = calc(str[i]);
        memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
        nxt[i][x] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        tot = 0;
        for (int j = 0; j < 16; ++j)
            if (nxt[i][j] <= n)
                p[++tot] = make_pair(nxt[i][j], j);
        sort(p + 1, p + 1 + tot);
        p[tot + 1] = make_pair(n + 1, 0);
        int now = 0;
        for (int j = 1; j <= tot; ++j)
        {
            now |= 1 << p[j].second;
            add(dp[now], p[j + 1].first - p[j].first);
            add(f[now], p[j + 1].first - p[j].first);
        }
    }
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                add(dp[i + j + k], dp[j + k]);
    int ans = (int)((ll)n * n % mod * (n + 1) % mod * (n + 1) % mod * inv4 % mod);
    for (int i = 0; i < m; ++i)
        dec(ans, (int)((ll)f[i] * dp[(m - 1) ^ i] % mod));
    printf("%d\n", ans);
    memset(dp, 0, sizeof(dp));
    memset(f, 0, sizeof(f));
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}