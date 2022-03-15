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
constexpr int N = 1e4 + 5, M = (1 << 24) + 5;
constexpr int m = (1 << 24);
int n, dp[M];
int p[8], tot;
char str[8];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str);
        tot = 0;
        for (int j = 0; j < 3; ++j)
            if (str[j] <= 'x')
                p[++tot] = str[j] - 'a';
        sort(p + 1, p + 1 + tot);
        tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
        switch (tot)
        {
        case 1:
            ++dp[1 << p[1]];
            break;
        case 2:
            ++dp[1 << p[1]];
            ++dp[1 << p[2]];
            --dp[1 << p[1] | 1 << p[2]];
            break;
        case 3:
            ++dp[1 << p[1]];
            ++dp[1 << p[2]];
            ++dp[1 << p[3]];
            --dp[1 << p[1] | 1 << p[2]];
            --dp[1 << p[1] | 1 << p[3]];
            --dp[1 << p[2] | 1 << p[3]];
            ++dp[1 << p[1] | 1 << p[2] | 1 << p[3]];
            break;
        }
    }
    for (int i = 1; (i << 1) <= m; i <<= 1)
        for (int j = 0; j < m; j += i << 1)
            for (int k = 0; k < i; ++k)
                dp[i + j + k] += dp[j + k];
    ll res = 0;
    for (int i = 0; i < m; ++i)
        res ^= (ll)dp[i] * dp[i];
    printf("%lld\n", res);
    return 0;
}