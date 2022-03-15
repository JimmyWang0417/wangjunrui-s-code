#include <cstdio>
#include <vector>
#include <climits>
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
constexpr int N = 2e6 + 5;
#define ws chznmsl
int wa[N], wb[N], ws[N];
int sa[N], rk[N];
int height[N];
inline bool cmp(int *r, int a, int b, int l)
{
    return r[a] == r[b] && r[a + l] == r[b + l];
}
inline void init(char *str, int n, int m)
{
    int *x = wa, *y = wb;

    fill(ws + 1, ws + 1 + m, 0);
    for (int i = 1; i <= n; ++i)
        ++ws[x[i] = str[i]];
    for (int i = 2; i <= m; ++i)
        ws[i] += ws[i - 1];
    for (int i = n; i >= 1; --i)
        sa[ws[x[i]]--] = i;

    for (int j = 1, p = 0; j < n && p < n; j <<= 1, m = p)
    {
        p = 0;
        for (int i = n - j + 1; i <= n; ++i)
            y[++p] = i;
        for (int i = 1; i <= n; ++i)
            if (sa[i] > j)
                y[++p] = sa[i] - j;

        fill(ws + 1, ws + 1 + m, 0);
        for (int i = 1; i <= n; ++i)
            ++ws[x[i]];
        for (int i = 2; i <= m; ++i)
            ws[i] += ws[i - 1];
        for (int i = n; i >= 1; --i)
            sa[ws[x[y[i]]]--] = y[i];

        swap(x, y);
        p = 0;
        for (int i = 1; i <= n; ++i)
            x[sa[i]] = cmp(y, sa[i], sa[i - 1], j) ? p : ++p;
    }
    for (int i = 1; i <= n; ++i)
        rk[sa[i]] = i;
    for (int i = 1, j = 0; i <= n; ++i)
    {
        if (j)
            --j;
        while (str[i + j] == str[sa[rk[i] - 1] + j])
            ++j;
        height[rk[i]] = j;
    }
}

inline void print(int n)
{
    for (int i = 1; i <= n; ++i)
        printf("%d ", sa[i]);
    putchar('\n');
    for (int i = 1; i <= n; ++i)
        printf("%d ", rk[i]);
    putchar('\n');
    for (int i = 1; i <= n; ++i)
        printf("%d ", height[i]);
    putchar('\n');
}
int Log[N];
int f[N][25];
int sum[N];
inline void work(int n, int m)
{
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + (sa[i] <= m);
        f[i][0] = height[i];
        Log[i] = Log[i >> 1] + 1;
    }
    for (int j = 1; j <= Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}
inline int lcp(int x, int y)
{
    if (x == y)
        return INT_MAX;
    x = rk[x], y = rk[y];
    if (x > y)
        swap(x, y);
    ++x;
    int k = Log[y - x + 1];
    return min(f[x][k], f[y - (1 << k) + 1][k]);
}
inline int query(int l, int r)
{
    return sum[r] - sum[l - 1];
}
char str[N];
int n, m, q;
int tot;
vector<pair<int, int>> g[N];
vector<pair<int, int>> que[N];
int answer[N], cnt;
int vis[N];
inline pair<int, int> get(int be, int en)
{
    pair<int, int> res;
    res.first = rk[be];
    int l = 1, r = rk[be] - 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (lcp(sa[mid], be) >= en - be + 1)
        {
            r = mid - 1;
            res.first = mid;
        }
        else
            l = mid + 1;
    }
    l = rk[be] + 1, r = tot, res.second = rk[be];
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (lcp(sa[mid], be) >= en - be + 1)
        {
            l = mid + 1;
            res.second = mid;
        }
        else
            r = mid - 1;
    }
    return res;
}
inline pair<int, int> merge(pair<int, int> a, pair<int, int> b, int len)
{
    if (a.first == -1 || a.second == -1 || b.first == -1 || b.second == -1)
        return make_pair(-1, -1);
    int l = a.first, r = a.second, ans = -1;
    pair<int, int> c;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (rk[sa[mid] + len] >= b.first)
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    if (ans != -1 || rk[sa[ans] + len] <= b.second)
        c.first = ans;
    else
        c.first = -1;
    l = c.first, r = a.second;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (rk[sa[mid] + len] <= b.second)
        {
            c.second = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return c;
}
inline void solve(int id)
{
    auto v = g[id].begin();
    pair<int, int> nmsl(1, tot);
    int now = 0;
    for (auto u : que[id])
    {
        while (v != g[id].end() && u.first > v->second)
        {
            nmsl = merge(nmsl, get(v->first, v->second), now);
            if (nmsl.first == -1 || nmsl.second == -1 || nmsl.first > nmsl.second)
                return;
            now += v->second - v->first + 1;
            ++v;
        }
        pair<int, int> res = merge(nmsl, get(v->first, u.first), now);
        if (res.first == -1 || res.second == -1 || res.first > res.second)
            return;
        answer[u.second] = query(res.first, res.second);
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("operator.in","r",stdin);
    freopen("operator.out","w",stdout);
#endif
    int chzcnm;
    read(chzcnm);
    read(n, m, q);
    scanf("%s", str + 1);
    tot = n;
    str[++tot] = '$';
    while (q--)
    {
        int opt;
        read(opt);
        if (opt == 1)
        {
            int x;
            read(x);
            if (vis[x])
            {
                if (vis[x] <= tot)
                    g[x].emplace_back(vis[x], tot);
                vis[x] = 0;
            }
            else
                vis[x] = tot + 1;
        }
        else if (opt == 2)
        {
            char cnm[3];
            scanf("%s", cnm);
            str[++tot] = cnm[0];
        }
        else
        {
            int x;
            read(x);
            ++cnt;
            if (vis[x] && vis[x] <= tot)
                que[x].emplace_back(tot, cnt);
            else if (!g[x].empty())
                que[x].emplace_back(g[x].back().second, cnt);
        }
    }
    for (int i = 1; i <= m; ++i)
        if (vis[i] && vis[i] <= tot)
            g[i].emplace_back(vis[i], tot);
    init(str, tot, 256);
    work(tot, n);
    // print(tot);
    for (int i = 1; i <= m; ++i)
        solve(i);
    for (int i = 1; i <= cnt; ++i)
        printf("%d\n", answer[i]);
    return 0;
}