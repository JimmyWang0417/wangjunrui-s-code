#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
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
constexpr int N = 2e4 + 5, M = 205;
int n, m;
int a[N];
ll dp[M][N];
struct node
{
    int k;
    ll b;
    node(int _k = 0, ll _b = 1e15) : k(_k), b(_b) {}
    inline ll calc(int x) { return (ll)k * x + b; }
};
struct Tree
{
    int l, r;
    node ans;
} tree[N * 40];
int root[N], cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void update(int &rt, int l, int r, node val)
{
    ++cnt;
    tree[cnt] = tree[rt];
    rt = cnt;
    int mid = (l + r) >> 1;
    ll res = val.calc(mid), ans = tree[rt].ans.calc(mid);
    if (l == r)
    {
        if (res < ans)
            tree[rt].ans = val;
        return;
    }
    if (val.k < tree[rt].ans.k)
    {
        if (res < ans)
        {
            update(lc(rt), l, mid, tree[rt].ans);
            tree[rt].ans = val;
        }
        else
            update(rc(rt), mid + 1, r, val);
    }
    else if (val.k > tree[rt].ans.k)
    {
        if (res < ans)
        {
            update(rc(rt), mid + 1, r, tree[rt].ans);
            tree[rt].ans = val;
        }
        else
            update(lc(rt), l, mid, val);
    }
    else
    {
        if (res < ans)
            tree[rt].ans = val;
    }
}
inline ll query(int rt, int l, int r, int pos)
{
    if (l == r)
        return tree[rt].ans.calc(pos);
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return min(tree[rt].ans.calc(pos), query(lc(rt), l, mid, pos));
    else
        return min(tree[rt].ans.calc(pos), query(rc(rt), mid + 1, r, pos));
}
int st[N], top;
deque<pair<int, ll>> g[N];
inline void merge(int x, int y)
{
    if (g[x].size() < g[y].size())
    {
        for (auto it = g[x].rbegin(); it != g[x].rend(); ++it)
        {
            while (g[y].size() >= 2 && (it->first - g[y][0].first) * (g[y][1].second - g[y][0].second) - (it->second - g[y][0].second) * (g[y][1].first - g[y][0].first) >= 0)
                g[y].pop_front();
            g[y].push_front(*it);
        }
        g[x].clear();
    }
    else
    {
        for (auto it = g[y].begin(); it != g[y].end(); ++it)
        {
            while (g[x].size() >= 2 && (g[x][g[x].size() - 1].first - g[x][g[x].size() - 2].first) * (it->second - g[x][g[x].size() - 1].second) - (g[x][g[x].size() - 1].second - g[x][g[x].size() - 2].second) * (it->first - g[x][g[x].size() - 1].first) <= 0)
                g[x].pop_back();
            g[x].push_back(*it);
        }
        swap(g[x], g[y]);
        g[x].clear();
    }
}
inline void print(int x)
{
    for (int i = 1; i < g[x].size(); ++i)
        printf("%lf ", (double)(g[x][i].second - g[x][i - 1].second) / (g[x][i].first - g[x][i - 1].first));
    putchar('\n');
}
inline ll query(int x, int k)
{
    int l = 0, r = (int)g[x].size() - 2;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if ((g[x][mid + 1].second - g[x][mid].second) <= (ll)k * (g[x][mid + 1].first - g[x][mid].first))
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -(ll)k * g[x][l].first + g[x][l].second;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
#endif
    read(n, m);
    dp[1][0] = 1e18;
    for (int i = 1, maxx = 0; i <= n; ++i)
    {
        read(a[i]);
        ckmax(maxx, a[i]);
        dp[1][i] = (ll)maxx * i;
    }
    for (int kase = 2; kase <= m; ++kase)
    {
        memset(root, cnt = 0, sizeof(root));
        for (int i = 0; i < kase; ++i)
            dp[kase][i] = 1e18;
        top = 0;
        for (int i = kase; i <= n; ++i)
        {
            g[i].clear();
            g[i].emplace_back(i - 1, dp[kase - 1][i - 1]);
            while (top && a[st[top]] <= a[i])
                merge(st[top--], i);
            root[i] = root[st[top]];
            update(root[i], 1, n, node(a[i], query(i, a[i])));
            st[++top] = i;
            dp[kase][i] = query(root[i], 1, n, i);
        }
    }
    printf("%lld\n", dp[m][n]);
    return 0;
}
