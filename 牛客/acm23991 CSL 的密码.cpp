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
    int ws[N], wa[N], wb[N], sa[N], rk[N], height[N];
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
    }
} a;
int n, m;
char str[N];
signed main()
{
    read(n, m);
    scanf("%s", str + 1);
    a.solve(str, n, 26);
    ll ans = (ll)(n - m + 1) * (n - m + 2) / 2;
    for (int i = 2; i <= n; ++i)
        ans -= max(0, a.height[i] - m + 1);
    printf("%lld\n", ans);
    return 0;
}