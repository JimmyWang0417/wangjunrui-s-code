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
constexpr int N = 2005;
int n;
char S[N], T[N];
int dp[N][N];
int f[N][26], g[N][26];
inline void work()
{
    read(n);
    scanf("%s%s", S + 1, T + 1);
    for (int i = 1; i <= n; ++i)
    {
        memcpy(f[i], f[i - 1], sizeof(f[i]));
        memcpy(g[i], g[i - 1], sizeof(g[i]));
        ++f[i][S[i] - 'a'];
        ++g[i][T[i] - 'a'];
    }
    for (int i = 0; i < 26; ++i)
        if (f[n][i] != g[n][i])
        {
            printf("-1\n");
            return;
        }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= n; ++i)
        dp[0][i] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
        {
            dp[i][j] = dp[i - 1][j] + 1;
            if (S[i] == T[j])
                ckmin(dp[i][j], dp[i - 1][j - 1]);
            if (f[i][T[j] - 'a'] < g[j][T[j] - 'a'])
                ckmin(dp[i][j], dp[i][j - 1]);
        }
    printf("%d\n", dp[n][n]);
}
signed main()
{
    int TT;
    read(TT);
    while (TT--)
        work();
    return 0;
}