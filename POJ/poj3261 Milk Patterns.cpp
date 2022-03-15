#include <cstdio>
#include <iostream>
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
const int N = 1e5 + 5;
int n, k;
struct suffix_array
{
    int ws[N], wa[N], wb[N];
    int sa[N], rk[N], height[N];
    inline bool cmp(int *r, int a, int b, int l)
    {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }
    inline void solve(int *str, int m)
    {
        int *x = wa, *y = wb;

        for (int i = 1; i <= n; ++i)
            ++ws[x[i] = str[i]];
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
    inline bool check(int mid)
    {
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (height[i] < mid)
                cnt = 1;
            else
                ++cnt;
            if (cnt >= k)
                return true;
        }
        return false;
    }
} a;
int str[N];
signed main()
{
    read(n), read(k);
    for (int i = 1; i <= n; ++i)
    {
        read(str[i]);
        ++str[i];
    }
    a.solve(str, 1e5 + 1);
    int l = 1, r = n, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (a.check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}