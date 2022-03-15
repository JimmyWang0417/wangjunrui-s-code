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
using namespace std;
const int N = 2e5 + 5;
struct suffix_array
{
    int Log[N];
    int ws[N], wa[N], wb[N];
    int rk[N], sa[N], height[N];
    int best[N][20];
    inline bool cmp(int *r, int a, int b, int l)
    {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    inline void solve(char *s, int n, int m)
    {
        int *x = wa, *y = wb;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i] = s[i] - 'a' + 1];
        for (int i = 2; i <= m; ++i)
            ws[i] += ws[i - 1];
        for (int i = n; i >= 1; --i)
            sa[ws[x[i]]--] = i;
        fill(ws + 1, ws + 1 + m, 0);

        for (int j = 1, p = 0; p < n; m = p, j <<= 1)
        {
            p = 0;
            for (int i = n - j + 1; i <= n; ++i)
                y[++p] = i;
            for (int i = 1; i <= n; ++i)
                if (sa[i] > j)
                    y[++p] = sa[i] - j;

            for (int i = 1; i <= n; ++i)
                ++ws[x[i]];
            for (int i = 2; i <= m; ++i)
                ws[i] += ws[i - 1];
            for (int i = n; i >= 1; --i)
                sa[ws[x[y[i]]]--] = y[i];
            fill(ws + 1, ws + 1 + m, 0);

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
            while (s[i + j] == s[sa[rk[i] - 1] + j])
                ++j;
            height[rk[i]] = j;
        }
    }
    inline int getmin(int x, int y)
    {
        return height[x] < height[y] ? x : y;
    }
    inline void init(int n)
    {
        Log[0] = -1;
        for (int i = 1; i <= n; ++i)
        {
            best[i][0] = i;
            Log[i] = Log[i >> 1] + 1;
        }
        for (int j = 1; j <= Log[n]; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                best[i][j] = getmin(best[i][j - 1], best[i + (1 << (j - 1))][j - 1]);
    }
    inline int query(int x, int y)
    {
        if (x > y)
            swap(x, y);
        ++x;
        int k = Log[y - x + 1];
        return getmin(best[x][k], best[y - (1 << k) + 1][k]);
    }
} sa;
int n;
int a[N], b[N];
char str[N];
int root[N];
int ch[N * 30][2], tot;
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
inline void insert(int u, int val)
{
    for (int i = 30; i >= 0; --i)
    {
        int c = (val >> i) & 1;
        ch[u][c] = ++tot;
        u = ch[u][c];
    }
}
inline int query(int u, int val)
{
    int ans = 0;
    for (int i = 30; i >= 0; --i)
    {
        int c = (val >> i) & 1;
        if (ch[u][!c])
        {
            ans |= 1 << i;
            u = ch[u][!c];
        }
        else
            u = ch[u][c];
    }
    return ans;
}
inline int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    lc(x) = merge(lc(x), lc(y));
    rc(x) = merge(rc(x), rc(y));
    return x;
}
inline ll solve(int l, int r)
{
    if (l == r)
    {
        root[l] = ++tot;
        insert(root[l], b[l]);
        return -1e18;
    }
    int pos = sa.query(l, r);
    ll res = max(solve(l, pos - 1), solve(pos, r));
    if (pos - l <= r - pos + 1)
    {
        for (int i = l; i < pos; ++i)
            res = max(res, (ll)sa.height[pos] + query(root[pos], b[i]));
    }
    else
    {
        for (int i = pos; i <= r; ++i)
            res = max(res, (ll)sa.height[pos] + query(root[l], b[i]));
    }
    // printf("%d %d %d %lld\n", l, pos,r, res);
    root[l] = merge(root[l], root[pos]);
    return res;
}
signed main()
{
    read(n);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    sa.solve(str, n, 26);
    sa.init(n);
    for (int i = 1; i <= n; ++i)
        b[sa.rk[i]] = a[i];
    printf("%lld\n", solve(1, n));
    return 0;
}