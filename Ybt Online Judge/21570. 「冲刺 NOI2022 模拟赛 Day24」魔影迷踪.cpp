#include <bitset>
#include <cstdio>
#include <iostream>
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
constexpr int N = 505;
constexpr int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, q;
bitset<N> dp[11][N][N];
int root[N];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
int dep[N];
char str[N][N];
int where[N];
inline void build(int rt, int l, int r)
{
    dep[rt] = dep[rt >> 1] + 1;
    int mid = (l + r) >> 1;
    for (int i = 1; i <= n; ++i)
        if (str[mid][i] == '.')
        {
            if (str[mid][i - 1] == '.')
                dp[dep[rt]][mid][i] = dp[dep[rt]][mid][i - 1];
            dp[dep[rt]][mid][i].set(i);
        }
    for (int i = mid + 1; i <= r; ++i)
        for (int j = 1; j <= n; ++j)
            if (str[i][j] == '.')
            {
                if (str[i - 1][j] == '.')
                    dp[dep[rt]][i][j] = dp[dep[rt]][i - 1][j];
                if (str[i][j - 1] == '.')
                    dp[dep[rt]][i][j] |= dp[dep[rt]][i][j - 1];
            }

    for (int i = n; i >= 1; --i)
        if (str[mid][i] == '.')
        {
            if (str[mid][i + 1] == '.')
                dp[dep[rt]][mid][i] = dp[dep[rt]][mid][i + 1];
            else
                dp[dep[rt]][mid][i].reset();
            dp[dep[rt]][mid][i].set(i);
        }
    for (int i = mid - 1; i >= l; --i)
        for (int j = n; j >= 1; --j)
            if (str[i][j] == '.')
            {
                if (str[i + 1][j] == '.')
                    dp[dep[rt]][i][j] = dp[dep[rt]][i + 1][j];
                if (str[i][j + 1] == '.')
                    dp[dep[rt]][i][j] |= dp[dep[rt]][i][j + 1];
            }
    if (l == r)
    {
        where[l] = rt;
        return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
#endif
    int type;
    read(n, type);
    for (int i = 1; i <= n; ++i)
        scanf("%s", str[i] + 1);
    build(1, 1, n);
    read(q);
    if (type)
        for (int i = 1, now = 2, all = 0; i <= q; ++i, add(now, now))
        {
            int x1, y1, x2, y2;
            read(x1, y1, x2, y2);
            x1 ^= all, y1 ^= all, x2 ^= all, y2 ^= all;
            if (x1 > x2 || y1 > y2)
            {
                add(all, 1);
                puts("No");
            }
            else if (x1 == x2)
            {
                if (dp[dep[where[x1]]][x1][y1][y2])
                {
                    add(all, now);
                    puts("Yes");
                }
                else
                {
                    add(all, 1);
                    puts("No");
                }
            }
            else
            {
                int u = where[x1], v = where[x2];
                if (dep[u] < dep[v])
                    swap(u, v);
                while (dep[u] > dep[v])
                    u >>= 1;
                while (u != v)
                {
                    u >>= 1;
                    v >>= 1;
                }
                if ((dp[dep[u]][x1][y1] & dp[dep[v]][x2][y2]).any())
                {
                    add(all, now);
                    puts("Yes");
                }
                else
                {
                    add(all, 1);
                    puts("No");
                }
            }
        }
    else
        for (int i = 1; i <= q; ++i)
        {
            int x1, y1, x2, y2;
            read(x1, y1, x2, y2);
            if (x1 > x2 || y1 > y2)
                puts("No");
            else if (x1 == x2)
                puts(dp[dep[where[x1]]][x1][y1][y2] ? "Yes" : "No");
            else
            {
                int u = where[x1], v = where[x2];
                if (dep[u] < dep[v])
                    swap(u, v);
                while (dep[u] > dep[v])
                    u >>= 1;
                while (u != v)
                {
                    u >>= 1;
                    v >>= 1;
                }
                puts((dp[dep[u]][x1][y1] & dp[dep[v]][x2][y2]).any() ? "Yes" : "No");
            }
        }
    return 0;
}
