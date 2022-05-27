// Problem: E. Yurii Can Do Everything
// Contest: Codeforces - Codeforces Round #682 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1438/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/extc++.h>
#include <bits/stdc++.h>
#define int ll
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
vector<int> g[35];
inline int calc(int x)
{
    int res = 0;
    while (x)
    {
        x >>= 1;
        ++res;
    }
    return res;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        g[calc(a[i])].push_back(i);
    }
    int ans = 0;
    for (int i = 1; i <= 31; ++i)
    {
        for (auto l : g[i])
        {
            int maxx = 1ll << i;
            for (int r = l + 2, sum = a[l + 1]; r <= n && sum < maxx; sum += a[r++])
                if (sum == (a[l] ^ a[r]))
                    ++ans;
        }
    }
    for (int i = 1; i <= 31; ++i)
    {
        for (auto r : g[i])
        {
            int maxx = 1ll << i;
            for (int l = r - 2, sum = a[r - 1]; l >= 1 && sum < maxx; sum += a[l--])
                if (sum == (a[l] ^ a[r]) && calc(a[l]) < i)
                    ++ans;
        }
    }
    printf("%lld\n", ans);
    return 0;
}