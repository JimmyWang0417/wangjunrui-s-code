// Problem: F. Bear and Bowling 4
// Contest: Codeforces - Educational Codeforces Round 11
// URL: https://codeforces.com/problemset/problem/660/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#include <bits/extc++.h>
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
constexpr int N = 2e5 + 5;
int n, a[N];
ll b[N], c[N];
int X[N];
ll Y[N];
int tot;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        b[i] = b[i - 1] + a[i];
        c[i] = c[i - 1] + (ll)a[i] * i;
    }
    ll ans = 0;
    ++tot;
    for (int i = 1; i <= n; ++i)
    {
        int l = 1, r = tot - 1, res = tot;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if ((double)(Y[mid + 1] - Y[mid]) / (X[mid + 1] - X[mid]) <= b[i])
            {
                res = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        res = X[res];
        ckmax(ans, (c[i] - c[res]) - (b[i] - b[res]) * res);
        ll now = b[i] * i - c[i];
        while (tot >= 2 && (X[tot - 1] - X[tot]) * (now - Y[tot]) <= (i - X[tot]) * (Y[tot - 1] - Y[tot]))
            --tot;
        ++tot, X[tot] = i, Y[tot] = now;
    }
    printf("%lld\n", ans);
    return 0;
}