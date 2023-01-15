/**
 *    unicode: UTF-8
 *    name:    CF1466G Song of the Sirens
 *    author:  whitepaperdog
 *    created: 2022.07.20 周三 09:37:23 (Asia/Shanghai)
 **/
#include <cstdio>
#include <cstring>
#define ll long long
#define lll __int128
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
constexpr int N = 1e5 + 5, M = 1e6 + 5;
constexpr int mod = 1e9 + 7;
constexpr int inv2 = (mod + 1) / 2;
int n, m, q, limit, limitlen;
ll power[N], invpower[N];
char S[M], T[N], str[25][M * 2], qwq[M * 2];
ll sum[N][26];
int p[M];
inline void init(char *s)
{
    p[1] = 0;
    for (int i = 2, j = 0; s[i]; ++i)
    {
        while (j && s[i] != s[j + 1])
            j = p[j];
        if (s[i] == s[j + 1])
            ++j;
        p[i] = j;
    }
}
inline int kmp(char *s, char *t)
{
    int res = 0;
    for (int i = 1, j = 0; s[i]; ++i)
    {
        while (j && s[i] != t[j + 1])
            j = p[j];
        if (s[i] == t[j + 1])
            ++j;
        if (!t[j + 1])
            ++res;
    }
    return res;
}
inline void work()
{
    ll ans = 0;
    int k;
    read(k);
    scanf("%s", S + 1);
    int len = (int)strlen(S + 1);
    init(S);
    if (m >= len)
        (ans += kmp(str[0], S)) %= mod;
    int where = m + 1;
    for (int i = 1, now = m; i <= k; ++i, now = now * 2 + 1)
    {
        if (now >= len - 1)
        {
            where = i;
            break;
        }
        if (now * 2 + 1 >= len)
            (ans += invpower[i] * kmp(str[i], S)) %= mod;
    }
    if (where <= k)
        for (int i = 0; i < 26; ++i)
        {
            ll times = sum[k][i] - sum[where - 1][i];
            if (times)
            {
                qwq[len] = (char)(i + 'a');
                for (int j = 1; j < len; ++j)
                {
                    qwq[len - j] = str[limit][limitlen - j + 1];
                    qwq[j + len] = str[limit][j];
                }
                qwq[len * 2] = 0;
                (ans += times * kmp(qwq, S)) %= mod;
            }
        }
    printf("%lld\n", (ans * power[k] % mod + mod) % mod);
}
signed main()
{
    read(n, q);
    power[0] = invpower[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        power[i] = power[i - 1] * 2 % mod;
        invpower[i] = invpower[i - 1] * inv2 % mod;
    }
    scanf("%s%s", str[0] + 1, T + 1);
    for (int i = 1, now = m = (int)strlen(str[0] + 1); i <= n && now <= 1e6; ++i, now = now * 2 + 1)
    {
        str[i][now + 1] = T[i];
        for (int j = 1; j <= now; ++j)
            str[i][j] = str[i][j + now + 1] = str[i - 1][j];
        limit = i;
        limitlen = now * 2 + 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        memcpy(sum[i], sum[i - 1], sizeof(sum[0]));
        (sum[i][T[i] - 'a'] += invpower[i]) %= mod;
    }
    while (q--)
        work();
    return 0;
}