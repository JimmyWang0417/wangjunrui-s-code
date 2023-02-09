/**
 *    unicode: UTF-8
 *    name:    CF1394C Boboniu and String
 *    author:  whitepaperdog
 *    created: 2022.07.10 周日 21:43:46 (Asia/Shanghai)
 **/
#include <cstdio>
#include <algorithm>
#define ll long long
#define lll __int128
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
constexpr int N = 3e5 + 5;
int n, a[N], b[N];
char str[N * 2];
inline bool check(int l)
{
    int mina = 0, maxa = 0x7fffffff;
    int minb = 0, maxb = 0x7fffffff;
    int minab = ~0x7fffffff, maxab = 0x7fffffff;
    for (int i = 1; i <= n; ++i)
    {
        ckmax(mina, a[i] - l), ckmin(maxa, a[i] + l);
        ckmax(minb, b[i] - l), ckmin(maxb, b[i] + l);
        ckmax(minab, a[i] - b[i] - l), ckmin(maxab, a[i] - b[i] + l);
    }
    return mina <= maxa && minb <= maxb &&
           minab <= maxab &&
           mina - maxb <= maxab && maxa - minb >= minab;
}
inline void solve(int l)
{
    int mina = 0, maxa = 0x7fffffff;
    int minb = 0, maxb = 0x7fffffff;
    int minab = ~0x7fffffff, maxab = 0x7fffffff;
    for (int i = 1; i <= n; ++i)
    {
        ckmax(mina, a[i] - l), ckmin(maxa, a[i] + l);
        ckmax(minb, b[i] - l), ckmin(maxb, b[i] + l);
        ckmax(minab, a[i] - b[i] - l), ckmin(maxab, a[i] - b[i] + l);
    }
    ckmax(mina, minb + minab), ckmin(maxa, maxb + maxab);
    ckmax(minb, mina - maxab), ckmin(maxb, maxa - minab);
    printf("%d\n", l);
    for (int i = 1; i <= maxa; ++i)
        putchar('B');
    for (int i = 1; i <= min(maxa - minab, maxb); ++i)
        putchar('N');
    putchar('\n');
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str + 1);
        for (int j = 1; str[j]; ++j)
            if (str[j] == 'B')
                ++a[i];
            else
                ++b[i];
    }
    int l = 0, r = 5e5;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    solve(l);
    return 0;
}