#include <bits/stdc++.h>
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
constexpr int N = 1e5 + 5;
int n, a[2 * N];
inline bool check(int mid)
{
    for (int i = 0; i < n; ++i)
    {
        if (a[n - i] < mid && a[n - i - 1] < mid)
            return false;
        if (a[n + i] < mid && a[n + i + 1] < mid)
            return false;
        if (a[n - i] >= mid && a[n - i - 1] >= mid)
            return true;
        if (a[n + i] >= mid && a[n + i + 1] >= mid)
            return true;
    }
    return a[1] >= mid;
}
signed main()
{
    read(n);
    for (int i = 1; i < 2 * n; ++i)
        read(a[i]);
    int l = 1, r = 2 * n - 1, ans = 0;
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
    return 0;
}