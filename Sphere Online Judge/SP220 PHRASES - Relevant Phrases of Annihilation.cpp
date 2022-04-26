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
const int N = 2.2e5 + 5;
struct suffix_array
{
    int ws[N], wa[N], wb[N];
    int sa[N], rk[N], height[N];
    inline bool cmp(int *r, int a, int b, int l)
    {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    inline void solve(int *str, int n, int m)
    {
        int *x = wa, *y = wb;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i] = str[i]];
        for (int i = 2; i <= m; ++i)
            ws[i] += ws[i - 1];
        for (int i = n; i >= 1; --i)
            sa[ws[x[i]]--] = i;
        fill(ws + 1, ws + 1 + m, 0);

        for (int j = 1, p = 0; p < n && j < n; j <<= 1, m = p)
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
        // for (int i = 1; i <= n; ++i)
        //     printf("%d ", sa[i]);
        // putchar('\n');
        // for (int i = 1; i <= n; ++i)
        //     printf("%d ", rk[i]);
        // putchar('\n');
        // for (int i = 1; i <= n; ++i)
        //     printf("%d ", height[i]);
        // putchar('\n');
    }
} sa;
int n, m;
int a[N];
int g[N];
char str[N];
int id[N];
int maxx[15], minn[15], S;
inline bool check(int mid)
{
    for (int i = 1; i <= m; ++i)
    {
        if (sa.height[i] < mid)
        {
            memset(maxx, ~0x3f, sizeof(maxx));
            memset(minn, 0x3f, sizeof(minn));
            S = 0;
            ckmin(minn[id[sa.sa[i]]], sa.sa[i]);
            ckmax(maxx[id[sa.sa[i]]], sa.sa[i]);
            if (maxx[id[sa.sa[i]]] - minn[id[sa.sa[i]]] >= mid)
                S |= 1 << id[sa.sa[i]];
        }
        else
        {
            ckmin(minn[id[sa.sa[i]]], sa.sa[i]);
            ckmax(maxx[id[sa.sa[i]]], sa.sa[i]);
            if (maxx[id[sa.sa[i]]] - minn[id[sa.sa[i]]] >= mid)
                S |= 1 << id[sa.sa[i]];
        }
        if (g[S >> 1] >= n)
            return true;
    }
    return false;
}
inline void work()
{
    m = 0;
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str + 1);
        for (int j = 1; str[j]; ++j)
        {
            a[++m] = str[j] - 'a' + 1;
            id[m] = i;
        }
        a[++m] = 26 + i;
    }
    sa.solve(a, m, n + 26);
    int l = 1, r = m, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
}
signed main()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < (1 << i); ++j)
            g[j | 1 << i] = g[j] + 1;
    }
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}