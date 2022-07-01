#include <cstdio>
#include <cstring>
#include <vector>
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
constexpr int N = 705;
constexpr int mod = 1e9 + 7;
template <typename T>
inline void add(T &x, T y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
char str[N];
int n;
pair<int, int> dp[N];
bool vis[N];
inline pair<int, int> dfs(int pos, int color, bool limit)
{
    if (pos == n + 1)
        return make_pair(0, 1);
    if (vis[pos] && !limit)
        return dp[pos];
    int res = 0, cnt = 0, maxx = limit ? str[pos] - '0' : 9;
    for (int i = 0; i <= maxx; ++i)
    {
        pair<int, int> now = dfs(pos + 1, color, limit && i == maxx);
        if (i < color)
        {
            add(res, now.first);
            add(cnt, now.second);
        }
        else
        {
            add(res, (int)((now.first * 10ll + now.second) % mod));
            add(cnt, now.second);
        }
    }
    if (!limit)
    {
        vis[pos] = true;
        dp[pos] = make_pair(res, cnt);
    }
    return make_pair(res, cnt);
}
signed main()
{
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    int res = 0;
    for (int i = 9; i >= 1; --i)
    {
        add(res, dfs(1, i, true).first);
        memset(vis, 0, sizeof(vis));
    }
    printf("%d\n", res);
    return 0;
}