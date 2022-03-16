#include <algorithm>
#include <cstdio>
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
inline void read(T &x, T1 &... x1)
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
constexpr int N = 5e5 + 5;
int n, q, a[N];
int f[N][2];
inline bool check(int l, int r)
{
    return f[r][0] <= l;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
#endif
    read(n, q);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1, l = 1; i <= n; ++i)
    {
        if (a[i] > a[i - 1])
            l = i;
        f[i][0] = l;
    }
    for (int i = 1, l = 1; i <= n; ++i)
    {
        if (a[i] < a[i - 1])
            l = i;
        ckmin(f[i][0], l);
    }
    for (int i = n, r = n; i >= 1; --i)
    {
        if (a[i] > a[i + 1])
            r = i;
        f[i][1] = r;
    }
    for (int i = n, r = n; i >= 1; --i)
    {
        if (a[i] < a[i + 1])
            r = i;
        ckmax(f[i][1], r);
    }
    for (int i = 1; i <= q; ++i)
    {
        int x, y;
        read(x, y);
        int l = 0, r = (y - x) / 2, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(x + mid, y - mid) || check(x + mid + 1, y - mid) || check(x + mid, y - mid - 1) ||
                check(x + mid, y - mid - 2) || check(x + mid + 2, y - mid))
            {
                r = mid - 1;
                ans = mid;
            }
            else
                l = mid + 1;
        }
        if (check(x + ans, y - ans))
            putchar('S');
        else if (check(x + ans + 1, y - ans) || check(x + ans, y - ans - 1))
            putchar('F');
        else if (f[x + ans][1] == y - ans - 2)
        {
            if (f[y - ans][0] > f[y - ans - 1][0])
            {
                if (((x + ans) & 1) == (f[y - ans - 1][0] & 1))
                    putchar('F');
                else
                    putchar('S');
            }
            else
            {
                if (((x + ans) & 1) == (f[y - ans][0] & 1))
                    putchar('S');
                else
                    putchar('F');
            }
        }
        else
        {
            if (f[x + ans][1] < f[x + ans + 1][1])
            {
                if (((y - ans) & 1) == (f[x + ans + 1][1] & 1))
                    putchar('F');
                else
                    putchar('S');
            }
            else
            {
                if (((y - ans) & 1) == (f[x + ans][1] & 1))
                    putchar('S');
                else
                    putchar('F');
            }
        }
    }
    putchar('\n');
    return 0;
}
