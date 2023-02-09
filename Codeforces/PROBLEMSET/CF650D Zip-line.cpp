#include <algorithm>
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
constexpr int N = 4e5 + 5;
int n, m, a[N];
int p[N], tot;
int c[N];
inline void update(int pos, int val)
{
    for (int i = pos; i <= tot; i += lowbit(i))
        ckmax(c[i], val);
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        ckmax(res, c[i]);
    return res;
}
int dp[2][N], mp[N];
vector<pair<int, int>> g[N];
struct node
{
    int pre, suf, ans;
} answer[N];
int where[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[i] = a[i];
    }
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
        a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
    for (int i = 1; i <= m; ++i)
    {
        int x;
        read(where[i], x);
        g[where[i]].emplace_back(i, x);
    }
    for (int i = 1; i <= n; ++i)
    {
        dp[0][i] = query(a[i] - 1);
        for (auto u : g[i])
            answer[u.first].pre = query((int)(lower_bound(p + 1, p + 1 + tot, u.second) - p - 1));
        update(a[i], dp[0][i] + 1);
    }
    memset(c, 0, sizeof(c));
    int ans = 1;
    for (int i = n; i >= 1; --i)
    {
        dp[1][i] = query(tot - a[i]);
        for (auto u : g[i])
            answer[u.first].suf = query(tot + 1 - (int)(upper_bound(p + 1, p + 1 + tot, u.second) - p));
        update(tot + 1 - a[i], dp[1][i] + 1);
        ckmax(ans, dp[0][i] + dp[1][i] + 1);
    }
    for (int i = 1; i <= n; ++i)
        if (ans == dp[0][i] + dp[1][i] + 1)
            ++mp[dp[0][i]];
    for (int i = 1; i <= m; ++i)
    {
        answer[i].ans = answer[i].pre + answer[i].suf + 1;
        if (dp[0][where[i]] + dp[1][where[i]] + 1 == ans && mp[dp[0][where[i]]] == 1)
            ckmax(answer[i].ans, ans - 1);
        else
            ckmax(answer[i].ans, ans);
        printf("%d\n", answer[i].ans);
    }
    return 0;
}