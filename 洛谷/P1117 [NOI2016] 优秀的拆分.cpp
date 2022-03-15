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
const int N = 6e4 + 5;
int Log[N];
struct suffix_array
{
    int ws[N], wa[N], wb[N];
    int sa[N], rk[N], height[N];
    int best[N][20];
    inline bool cmp(int *r, int a, int b, int l)
    {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    inline void solve(char *str, int n, int m)
    {
        int *x = wa, *y = wb;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i] = str[i] - 'a' + 1];
        for (int i = 2; i <= m; ++i)
            ws[i] += ws[i - 1];
        for (int i = n; i >= 1; --i)
            sa[ws[x[i]]--] = i;
        fill(ws + 1, ws + 1 + m, 0);

        for (int j = 1, p = 0; p < n; j <<= 1, m = p)
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
            while (str[i + j] == str[sa[rk[i] - 1] + j])
                ++j;
            height[rk[i]] = j;
        }
    }
    inline void init(int n)
    {
        for (int i = 1; i <= n; ++i)
            best[i][0] = height[i];
        for (int j = 1; j <= Log[n]; ++j)
        {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                best[i][j] = min(best[i][j - 1], best[i + (1 << (j - 1))][j - 1]);
        }
    }
    inline int query(int x, int y)
    {
        x = rk[x], y = rk[y];
        if (x > y)
            swap(x, y);
        ++x;
        int k = Log[y - x + 1];
        return min(best[x][k], best[y - (1 << k) + 1][k]);
    }
    inline void clear()
    {
        memset(wa, 0, sizeof(wa));
        memset(wb, 0, sizeof(wb));
    }
} strarray, revstrarray;
char str[N];
int n;
int pre[N], suf[N];
signed main()
{
    Log[0] = -1;
    for (int i = 1; i <= 3e4; ++i)
        Log[i] = Log[i >> 1] + 1;
    int T;
    read(T);
    while (T--)
    {
        scanf("%s", str + 1);
        n = (int)strlen(str + 1);
        strarray.solve(str, n, 26);
        strarray.init(n);
        reverse(str + 1, str + 1 + n);
        revstrarray.solve(str, n, 26);
        revstrarray.init(n);
        for (int len = 1; len <= n; ++len)
        {
            for (int i = 1; i + len <= n; i += len)
            {
                int lcp = strarray.query(i, i + len), lcs = revstrarray.query(n + 1 - i, n + 1 - i - len);
                // printf("%d %d %d lcp=%d lcs=%d\n", len, i, i + len, lcp, lcs);
                if (lcp + lcs - 1 >= len)
                {
                    ++pre[i + len + max(len - lcs, 0)];
                    --pre[i + len + min(lcp, len)];
                    ++suf[i - max(len - lcp, 0)];
                    --suf[i - min(lcs, len)];
                }
            }
        }
        for (int i = 1; i <= n; ++i)
            pre[i] += pre[i - 1];
        for (int i = n; i >= 1; --i)
            suf[i] += suf[i + 1];
        ll ans = 0;
        for (int i = 1; i < n; ++i)
            ans += (ll)pre[i] * suf[i + 1];
        printf("%lld\n", ans);
        strarray.clear(), revstrarray.clear();
        memset(pre, 0, sizeof(pre));
        memset(suf, 0, sizeof(suf));
    }
    return 0;
}