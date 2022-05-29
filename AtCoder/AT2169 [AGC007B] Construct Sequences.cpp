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
constexpr int N = 2e4 + 5;
int n;
int mp[N];
int a[N], b[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        mp[x] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        a[i] = i * n;
        b[i] = (n - i) * n + mp[i];
        printf("%d ", a[i]);
    }
    putchar('\n');
    for (int i = 1; i <= n; ++i)
        printf("%d ", b[i]);
    putchar('\n');
    return 0;
}