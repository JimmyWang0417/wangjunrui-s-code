#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 2e5 + 5;
int Log[N];
#define ws nmsl
int wa[N], wb[N], ws[N];
int sa[N], rk[N], height[N];
int f[N][25];
inline void work(int *s, int n, int m)
{
    int *x = wa, *y = wb;
    for (int i = 1; i <= n; ++i)
        ++ws[x[i] = s[i]];
    for (int i = 1; i <= m; ++i)
        ws[i] += ws[i - 1];
    for (int i = n; i >= 1; --i)
        sa[ws[x[i]]--] = i;
    fill(ws + 1, ws + 1 + m, 0);

    for (int j = 1, p = 0; j < n && p < n; j <<= 1, m = p)
    {
        p = 0;
        for (int i = n - j + 1; i <= n; ++i)
            y[++p] = i;
        for (int i = 1; i <= n; ++i)
            if (sa[i] > j)
                y[++p] = sa[i] - j;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i]];
        for (int i = 1; i <= m; ++i)
            ws[i] += ws[i - 1];
        for (int i = n; i >= 1; --i)
            sa[ws[x[y[i]]]--] = y[i];
        fill(ws + 1, ws + 1 + m, 0);

        swap(x, y);
        p = 0;
        for (int i = 1; i <= n; ++i)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j] ? p : ++p);
    }
    for (int i = 1; i <= n; ++i)
        rk[sa[i]] = i;
    for (int i = 1, j = 0; i <= n; ++i)
    {
        if (j)
            --j;
        while (s[i + j] == s[sa[rk[i] - 1] + j])
            ++j;
        height[rk[i]] = j;
    }
}
int n, q;
int mp[N];
int a[N];
char str[N];
inline int lcp(int x, int y)
{
    if (x == y)
        return n - x + 1;
    x = rk[x], y = rk[y];
    if (x > y)
        swap(x, y);
    ++x;
    int k = Log[y - x + 1];
    return min(f[x][k], f[y - (1 << k) + 1][k]);
}
int nxt[N][15];
struct node
{
    int a[15], cnt;
} b[N];
int id[N], pos[N];
int g[N][25];
inline void work()
{
    for (int i = 0; i <= 9; ++i)
        nxt[n + 1][i] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
        nxt[i][str[i] - '0'] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= 9; ++j)
            if (nxt[i][j] <= n)
                b[i].a[++b[i].cnt] = nxt[i][j];
        b[i].a[++b[i].cnt] = n + 1;
        sort(b[i].a + 1, b[i].a + b[i].cnt + 1);
    }
    for (int i = 1; i <= n; ++i)
        id[i] = i;
    auto comp = [](int x, int y)
    {
        for (int i = 1; i < b[x].cnt && i < b[y].cnt; ++i)
        {
            if (b[x].a[i + 1] - b[x].a[i] == b[y].a[i + 1] - b[y].a[i])
            {
                if (lcp(b[x].a[i] + 1, b[y].a[i] + 1) < b[x].a[i + 1] - b[x].a[i] - 1)
                    return rk[b[x].a[i] + 1] < rk[b[y].a[i] + 1];
            }
            else
                return lcp(b[x].a[i] + 1, b[y].a[i] + 1) >= min(b[x].a[i + 1] - b[x].a[i] - 1, b[y].a[i + 1] - b[y].a[i] - 1) ? b[x].a[i + 1] - b[x].a[i] - 1 < b[y].a[i + 1] - b[y].a[i] - 1 : rk[b[x].a[i] + 1] < rk[b[y].a[i] + 1];
        }
        return x > y;
    };
    sort(id + 1, id + 1 + n, comp);
    for (int i = 1; i <= n; ++i)
        pos[id[i]] = i;
    for (int now = 2; now <= n; ++now)
    {
        int x = id[now - 1], y = id[now];
        int &res = g[now][0];
        for (int i = 1; i < b[x].cnt && i < b[y].cnt; ++i)
        {
            ++res;
            if (b[x].a[i + 1] - b[x].a[i] == b[y].a[i + 1] - b[y].a[i])
            {
                int wdnmd = lcp(b[x].a[i] + 1, b[y].a[i] + 1);
                if (wdnmd < b[x].a[i + 1] - b[x].a[i] - 1)
                {
                    res += wdnmd;
                    break;
                }
                else
                    res += min(wdnmd, b[x].a[i + 1] - b[x].a[i] - 1);
            }
            else
            {
                res += min(lcp(b[x].a[i] + 1, b[y].a[i] + 1), min(b[x].a[i + 1] - b[x].a[i] - 1, b[y].a[i + 1] - b[y].a[i] - 1));
                break;
            }
        }
    }
    for (int j = 0; j < Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            g[i][j + 1] = min(g[i][j], g[i + (1 << j)][j]);
}
inline int query(int x, int y)
{
    ++x;
    int k = Log[y - x + 1];
    return min(g[x][k], g[y - (1 << k) + 1][k]);
}
signed main()
{
    freopen("similar.in", "r", stdin);
    freopen("similar.out", "w", stdout);
    read(n, q);
    scanf("%s", str + 1);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        Log[i] = Log[i >> 1] + 1;
        a[i] = mp[str[i] - '0'] ? i - mp[str[i] - '0'] : 0;
        mp[str[i] - '0'] = i;
    }
    work(a, n, n);
    for (int i = 1; i <= n; ++i)
        f[i][0] = height[i];
    for (int j = 0; j < Log[n]; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            f[i][j + 1] = min(f[i][j], f[i + (1 << j)][j]);
    work();
    int lastans = 0;
    while (q--)
    {
        int x, y;
        read(x, y);
        x ^= lastans, y ^= lastans;
        int len = y - x + 1;
        x = pos[x];
        lastans = 1;
        int l = 1, r = x - 1, res = x;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (query(mid, x) >= len)
            {
                res = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        lastans += x - res;
        l = x + 1, r = n, res = x;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (query(x, mid) >= len)
            {
                res = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("%d\n", lastans += res - x);
    }
    return 0;
}