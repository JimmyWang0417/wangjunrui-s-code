/**
 *    unicode: UTF-8
 *    name:    P5012 水の数列
 *    author:  wangjunrui
 *    created: 2022.07.22 周五 08:25:35 (Asia/Shanghai)
 **/
#include <cstdio>
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
constexpr int N = 1e6 + 5;
int n, m, a[N];
int Log[N];
struct node
{
    ll y;
    int x;
    node(ll _y = 0, int _x = 0) : y(_y), x(_x) {}
    inline bool operator<(const node &rhs) const
    {
        return y * rhs.x < rhs.y * x;
    }
} dp[N];
int tree[N * 4];
#define lc (rt << 1)

#define rc (rt << 1 | 1)

inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[rt] = dp[tree[lc]] < dp[tree[rc]] ? tree[rc] : tree[lc];
}
inline node query(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return dp[tree[rt]];
    int mid = (l + r) >> 1;
    if (y <= mid)
        return query(lc, l, mid, x, y);
    if (x > mid)
        return query(rc, mid + 1, r, x, y);
    return max(query(lc, l, mid, x, y), query(rc, mid + 1, r, x, y));
}
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
ll sum[N], sum2[N];
bool exist[N];
vector<int> g[N];
signed main()
{
    read(n, m);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        g[a[i]].push_back(i);
        Log[i] = Log[i >> 1] + 1;
        dp[i] = node(0, 1);
    }
    ll ans = 0;
    for (int i = 1, res = 0; i <= 1e6; ++i)
    {
        if (g[i].empty())
            continue;
        for (auto u : g[i])
        {
            exist[u] = true;
            if (exist[u - 1] && exist[u + 1])
            {
                int x = find(u - 1), y = find(u + 1);

                fa[x] = fa[u] = y;

                ans -= sum2[x] + sum2[y];

                sum2[y] += 1 + 2 * sum[y];
                ++sum[y];

                sum2[y] += sum2[x] + 2 * sum[x] * sum[y];
                sum[y] += sum[x];

                ans += sum2[y];

                --res;
            }
            else if (exist[u - 1])
            {
                int y = find(u - 1);

                ans -= sum2[y];

                fa[u] = y;

                sum2[y] += 1 + 2 * sum[y];
                ++sum[y];

                ans += sum2[y];
            }
            else if (exist[u + 1])
            {
                int y = find(u + 1);

                ans -= sum2[y];

                fa[u] = y;

                sum2[y] += 1 + 2 * sum[y];
                ++sum[y];

                ans += sum2[y];
            }
            else
            {
                sum[u] = sum2[u] = 1;
                ++res;
                ++ans;
            }
        }
        ckmax(dp[res], node(ans, i));
    }
    build(1, 1, n);
    ll lastans = 0;
    for (int i = 1; i <= m; ++i)
    {
        int qaq, qbq, x, y;
        read(qaq, qbq, x, y);
        int l = (int)((qaq * lastans + x - 1) % n + 1),
            r = (int)((qbq * lastans + y - 1) % n + 1);
        if (l > r)
            swap(l, r);
        node res = query(1, 1, n, l, r);
        ll nmsl = lastans;
        if (res.y)
        {
            printf("%lld %d\n", res.y, res.x);
            lastans = res.y * res.x;
        }
        else
        {
            printf("-1 -1\n");
            lastans = 1;
        }
        lastans %= n;
        printf("%d %d %lld\n", l, r, nmsl);
    }
    return 0;
}