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
const int N = 2005;
const int mod = 1e9 + 7;
int m, d;
int dp[N][N];
int dight[N], tot;
inline int dfs(int pos, int val, bool limit)
{
    if (pos > tot)
        return val == 0;
    if (!limit && dp[pos][val] != -1)
        return dp[pos][val];
    int maxx = limit ? dight[pos] : 9;
    int res = 0;
    if (pos & 1)
        for (int i = 0; i <= maxx; ++i)
        {
            if (i == d)
                continue;
            (res += dfs(pos + 1, (val * 10 + i) % m, limit && maxx == i)) %= mod;
        }
    else if (d <= maxx)
        res = dfs(pos + 1, (val * 10 + d) % m, limit && maxx == d);
    if (!limit)
        dp[pos][val] = res;
    return res;
}
char L[N], R[N];
inline int calc(char *s)
{
    tot = (int)strlen(s + 1);
    for (int i = 1; i <= tot; ++i)
        dight[i] = s[i] - '0';
    //	printf("%d\n",tot);
    //	for(int i=1; i<=tot; ++i)
    //		printf("%d ",dight[i]);
    //	putchar('\n');
    int res = 0;
    for (int i = 1; i <= dight[1]; ++i)
    {
        if (i == d)
            continue;
        (res += dfs(2, i % m, i == dight[1])) %= mod;
    }
    return res;
}
inline bool check(char *s)
{
    int val = 0;
    for (int i = 1; s[i]; ++i)
    {
        val = (val * 10 + s[i] - '0') % m;
        if (i & 1)
        {
            if (s[i] - '0' == d)
                return false;
        }
        else
        {
            if (s[i] - '0' != d)
                return false;
        }
    }
    return val == 0;
}
signed main()
{
    read(m, d);
    memset(dp, -1, sizeof(dp));
    scanf("%s%s", L + 1, R + 1);
    printf("%d\n", (calc(R) - calc(L) + check(L) + mod) % mod);
    return 0;
}
