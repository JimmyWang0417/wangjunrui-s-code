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
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
using namespace std;
const int N = 1e6 + 5;
struct Point
{
    int ch[2];
    int fa, len;
} point[N];
int tot = 1, las = 1;
#define calc(c) (c == '(' ? 0 : 1)
int dp[N];
inline void insert(int c, int id)
{
    int p = las, np = las = ++tot;
    point[np].len = point[p].len + 1;
    dp[np] = id;
    for (; p && !point[p].ch[c]; p = point[p].fa)
        point[p].ch[c] = np;
    if (!p)
        point[np].fa = 1;
    else
    {
        int q = point[p].ch[c];
        if (point[q].len == point[p].len + 1)
            point[np].fa = q;
        else
        {
            int nq = ++tot;
            point[nq] = point[q];
            point[nq].len = point[p].len + 1;
            point[np].fa = point[q].fa = nq;
            for (; p && point[p].ch[c] == q; p = point[p].fa)
                point[p].ch[c] = nq;
        }
    }
}
int n;
char str[N];
int nmsl[N];
int q[N];
vector<pair<int, int>> g[N];
int L[N];
int best[N][20], Log[N];
inline int query(int l, int r)
{
    int k = Log[r - l + 1];
    return min(best[l][k], best[r - (1 << k) + 1][k]);
}
inline void work()
{
    for (int i = 1; i <= tot; ++i)
        ++nmsl[point[i].len];
    for (int i = 1; i <= n; ++i)
        nmsl[i] += nmsl[i - 1];
    for (int i = tot; i >= 1; --i)
        q[nmsl[point[i].len]--] = i;
    for (int i = tot; i >= 2; --i)
    {
        int u = q[i];
        ckmax(dp[point[u].fa], dp[u]);
        int l = max(L[dp[u]], dp[u] - point[u].len + 1), r = dp[u] - point[point[u].fa].len;
        if (l <= r)
        {
            g[l].push_back(make_pair(best[dp[u] + 1][0], 1));
            g[r + 1].push_back(make_pair(best[dp[u] + 1][0], -1));
        }
    }
}
int buf[N], *cnt = &buf[N / 2];
signed main()
{
    read(n);
    scanf("%s", str + 1);
    Log[0] = -1;
    for (int i = 1; str[i]; ++i)
    {
        insert(calc(str[i]), i);
        Log[i] = Log[i >> 1] + 1;
    }
    for (int i = n; i >= 1; --i)
        best[i][0] = best[i + 1][0] + (str[i] == '(' ? -1 : 1);
    for (int j = 1; j <= Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            best[i][j] = min(best[i][j - 1], best[i + (1 << (j - 1))][j - 1]);
    for (int i = 1; i <= n; ++i)
    {
        int l = 1, r = i - 1, res = i;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (query(mid, i) >= best[i + 1][0])
            {
                res = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        L[i] = res;
    }
    work();
    ll ans = 0;
    for (int i = n; i >= 1; --i)
    {
        ++cnt[best[i][0]];
        for (auto v : g[i])
            ans += cnt[v.first] * v.second;
    }
    printf("%lld\n", ans);
    return 0;
}