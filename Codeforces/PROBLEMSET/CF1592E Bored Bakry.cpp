#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 1e6 + 6;
int n, a[N];
int mp[N];
int times;
int vis[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    int ans = 0;
    for (int i = 20; i >= 0; --i)
    {
        int l = 1, r;
        while (l <= n && !((a[l] >> i) & 1))
            ++l;
        for (; l <= n; l = r + 1)
        {
            ++times;
            r = l;
            mp[0] = l;
            vis[0] = times;
            int sum = 0;
            while ((a[r] >> i) & 1)
            {
                sum ^= (a[r] >> i);
                ++r;
                if (vis[sum] == times)
                    ckmax(ans, r - mp[sum]);
                else
                {
                    mp[sum] = r;
                    vis[sum] = times;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}