#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1005;
const int mod = 1e9 + 7;
int n, k, dight[N];
int dp[N][N][2];
inline int dfs(int pos, int lasluck, bool ok, bool limit)
{
    if (pos == 0)
        return ok;
    if (!limit && dp[pos][lasluck][ok] != -1)
        return dp[pos][lasluck][ok];
    int ans = 0, maxx = (limit ? dight[pos] : 9);
    for (int i = 0; i <= maxx; ++i)
    {
        if (i == 4 || i == 7)
            (ans += dfs(pos - 1, pos, ok || (abs(lasluck - pos) <= k && lasluck), limit && i == maxx)) %= mod;
        else
            (ans += dfs(pos - 1, lasluck, ok, limit && i == maxx)) %= mod;
    }
    if (!limit)
        dp[pos][lasluck][ok] = ans;
    return ans;
}
char lstr[N], rstr[N];
inline int calc(char *s)
{
    n = (int)strlen(s + 1);
    for (int i = 1; i <= n; ++i)
        dight[n - i + 1] = s[i] - '0';
    //	for(int i=n; i>=1; --i)
    //		printf("%d",dight[i]);
    //	putchar('\n');
    return dfs(n, 0, false, true);
}
inline bool solve(char *s)
{
    int lasluck = -1e9;
    for (int i = 1; s[i]; ++i)
    {
        if (s[i] == '4' || s[i] == '7')
        {
            if (i - lasluck <= k)
                return true;
            lasluck = i;
        }
    }
    return false;
}
inline void work()
{
    scanf("%s%s", lstr + 1, rstr + 1);
    printf("%d\n", (calc(rstr) - calc(lstr) + solve(lstr) + mod) % mod);
}
signed main()
{
    int T;
    read(T, k);
    memset(dp, -1, sizeof(dp));
    while (T--)
        work();
    return 0;
}
