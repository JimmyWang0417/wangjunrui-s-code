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
const int mod = 1000003;
const int N = 105, M = (1 << 15) + 5;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, k;
int f[M];
int G[N][26];
char str[N];
int dp[N][M];
inline void work()
{
    read(n, k);
    memset(G, 0, sizeof(G));
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", str);
        for (int j = 0; str[j]; ++j)
            if (str[j] == '?')
                for (int c = 0; c < 26; ++c)
                    G[j][c] |= (1 << i);
            else
                G[j][str[j] - 'a'] |= (1 << i);
    }
    m = (int)strlen(str);
    dp[0][(1 << n) - 1] = 1;
    for (int i = 0; i < m; ++i)
        for (int S = 0; S < (1 << n); ++S)
            if (f[S] >= k && dp[i][S])
            {
                for (int c = 0; c < 26; ++c)
                    if (f[S & G[i][c]] >= k)
                        add(dp[i + 1][S & G[i][c]], dp[i][S]);
            }
    int res = 0;
    for (int S = 0; S < (1 << n); ++S)
        if (f[S] == k)
            add(res, dp[m][S]);
    printf("%d\n", res);
    memset(dp, 0, sizeof(dp));
}
signed main()
{
    for (int i = 1; i < (1 << 15); ++i)
        f[i] = f[i ^ lowbit(i)] + 1;
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}