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
constexpr int N = (1 << 19) + 5;
int n, m, k, q;
char str[N];
int nxt[N][25], sum[N][25];
pair<int, int> p[N];
int tot;
ll dp[25][N];
inline void FWT(ll *f)
{
    for (int i = 1; i <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                f[i + j + k] += f[j + k];
}
signed main()
{
    read(n, k);
    m = (1 << k);
    scanf("%s", str + 1);
    for (int i = 0; i < k; ++i)
        nxt[n + 1][i] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
        nxt[i][str[i] - 'a'] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        memcpy(sum[i], sum[i - 1], sizeof(sum[i]));
        ++sum[i][str[i] - 'a'];
    }
    for (int i = 1; i <= n; ++i)
    {
        int c = str[i] - 'a';
        tot = 0;
        for (int j = 0; j < k; ++j)
            if (nxt[i][j] <= n)
                p[++tot] = make_pair(nxt[i][j], j);
        sort(p + 1, p + 1 + tot);
        int now = 0;
        p[tot + 1].first = n + 1;
        for (int j = 1; j <= tot; ++j)
        {
            now |= 1 << p[j].second;
            dp[c][now] += (sum[p[j + 1].first - 1][c] - sum[p[j].first - 1][c]) * 2;
        }
        --dp[c][1 << c];
    }
    for (int i = 0; i < k; ++i)
        FWT(dp[i]);
    read(q);
    while (q--)
    {
        scanf("%s", str);
        int S = 0;
        for (int i = 0; str[i]; ++i)
            S |= 1 << (str[i] - 'a');
        ll ans = 0;
        for (int i = 0; i < k; ++i)
            if (!((S >> i) & 1))
                ans += dp[i][S | 1 << i];
        printf("%lld\n", ans);
    }
    return 0;
}