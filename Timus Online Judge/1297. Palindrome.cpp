#include <algorithm>
#include <cstdio>
#include <cstring>
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
using namespace std;
const int N = 4005 + 5;
struct suffix_array
{
    int ws[N], wa[N], wb[N], sa[N], rk[N], height[N];
    inline bool cmp(int *r, int a, int b, int l)
    {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    inline void solve(char *s, int n, int m)
    {
        int *x = wa, *y = wb;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i] = s[i]];
        for (int i = 2; i <= m; ++i)
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
} a;
int n, m;
char str[N];
int best[N][15];
int Log[N];
inline int query(int l, int r)
{
    l = a.rk[l], r = a.rk[r];
    if (l > r)
        swap(l, r);
    ++l;
    int k = Log[r - l + 1];
    return min(best[l][k], best[r - (1 << k) + 1][k]);
}
signed main()
{
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    str[n + 1] = '$';
    m = 2 * n + 1;
    for (int i = 1; i <= n; ++i)
        str[m + 1 - i] = str[i];
    a.solve(str, m, 256);
    Log[0] = -1;
    for (int i = 1; i <= m; ++i)
        Log[i] = Log[i >> 1] + 1;
    for (int i = 1; i <= m; ++i)
        best[i][0] = a.height[i];
    for (int j = 1; j <= Log[m]; ++j)
    {
        for (int i = 1; i + (1 << j) - 1 <= m; ++i)
            best[i][j] = min(best[i][j - 1], best[i + (1 << (j - 1))][j - 1]);
    }
    int ans = 0, where = -1;
    for (int i = 1; i <= n; ++i)
    {
        int res = query(i, m + 1 - i);
        if (2 * res - 1 > ans)
        {
            ans = 2 * res - 1;
            where = i - res + 1;
        }
        res = query(i, m - i) - 1;
        if (2 * res > ans)
        {
            ans = 2 * res;
            where = i - res + 1;
        }
    }
    str[where + ans] = '\0';
    printf("%s\n", &str[where]);
    return 0;
}