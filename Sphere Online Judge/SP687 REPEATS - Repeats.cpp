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
const int N = 1e5 + 5;
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
struct suffix_array
{
    int ws[N], wa[N], wb[N];
    int sa[N], rk[N], height[N];
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

        for (int j = 1, p = 0; j < n && p < n; m = p, j <<= 1)
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
} sa;
char str[N];
int Log[N];
int best[N][20];
inline int query(int x, int y)
{
    x = sa.rk[x], y = sa.rk[y];
    if (x > y)
        swap(x, y);
    ++x;
    int k = Log[y - x + 1];
    return min(best[x][k], best[y - (1 << k) + 1][k]);
}
inline void work()
{
    int n;
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        char opt[10];
        scanf("%s", opt);
        str[i] = opt[0];
    }
    sa.solve(str, n, 26);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        best[i][0] = sa.height[i];
        Log[i] = Log[i >> 1] + 1;
    }
    for (int j = 1; j <= 16; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            best[i][j] = min(best[i][j - 1], best[i + (1 << (j - 1))][j - 1]);
    int ans = 1;
    for (int len = 1; len <= n; ++len)
        for (int i = 1; i + len <= n; i += len)
        {
            int lcp = query(i, i + len);
            int res = lcp / len + 1;
            int l = i - len + lcp % len;

            if (l > 0 && query(l, l + len) > len)
                ++res;
            ckmax(ans, res);
        }
    printf("%d\n", ans);
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}