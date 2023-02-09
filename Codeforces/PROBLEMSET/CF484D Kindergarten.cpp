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
const int N = 1e6 + 5;
int n, a[N];
ll f[N];
inline bool check(int x)
{
    return (a[x - 2] < a[x - 1] && a[x - 1] < a[x]) || (a[x - 2] > a[x - 1] && a[x - 1] > a[x]);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    f[2] = abs(a[1] - a[2]);
    for (int i = 3; i <= n; ++i)
    {
        if (check(i))
            f[i] = f[i - 1] + abs(a[i] - a[i - 1]);
        else
            f[i] = max(f[i - 1], f[i - 2] + abs(a[i] - a[i - 1]));
    }
    printf("%lld\n", f[n]);
    return 0;
}