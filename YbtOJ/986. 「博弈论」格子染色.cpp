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
constexpr int N = 1e5 + 5;
int n, k, a[N], vis[N], sg[N];
inline int SG1(int x)
{
    return sg[x <= 52 ? x : 52 + (x - 52) % 34];
}
inline int SG2(int l, int r)
{
    return 1 <= l && r <= n ? a[l] == a[r] : r - l - 1;
}
inline bool solve()
{
    int i, j, t = 0;
    if (k >= 3)
    {
        for (i = 1; i <= n; ++i)
            !a[i] && (t ^= 1);
        return t;
    }
    if (k == 1)
    {
        for (j = 0, i = 1; i <= n; ++i)
            a[i] && (t ^= SG1(max(j ? i - j - 3 : i - 2, 0)), j = i);
        return t ^= SG1(max(j ? n - j - 1 : n, 0)), t;
    }
    for (i = 1; i <= n && !a[i]; ++i)
        ;
    if (i > n)
        return n & 1;
    for (j = 0, i = 1; i <= n; ++i)
        a[i] && (t ^= SG2(j, i), j = i);
    return t ^= SG2(j, n + 1);
}
signed main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    sg[1] = 1;
    for (int i = 2; i <= 85; ++i)
    {
        vis[sg[i - 2]] = i;
        for (int j = 0; j <= i - 3; ++j)
            vis[sg[j] ^ sg[i - 3 - j]] = i;
        while (vis[sg[i]] == i)
            ++sg[i];
    }
    read(n, k);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    puts(solve() ? "YES" : "NO");
    return 0;
}