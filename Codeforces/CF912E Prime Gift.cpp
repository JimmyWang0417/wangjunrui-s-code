// Problem: E. Prime Gift
// Contest: Codeforces - Codeforces Round #456 (Div. 2)
// URL: https://codeforces.com/problemset/problem/912/E
// Memory Limit: 256 MB
// Time Limit: 3500 ms
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
constexpr ll MAX = 1e18;
int n, m;
vector<int> a1, a2;
vector<ll> ans1, ans2;
inline void dfs1(vector<int>::iterator it = a1.begin(), ll now = 1)
{
    ans1.push_back(now);
    for (; it != a1.end() && MAX / (*it) > now; ++it)
        dfs1(it, now * (*it));
}
inline void dfs2(vector<int>::iterator it = a2.begin(), ll now = 1)
{
    ans2.push_back(now);
    for (; it != a2.end() && MAX / (*it) > now; ++it)
        dfs2(it, now * (*it));
}
inline bool check(ll mid)
{
    ll sum = 0;
    for (auto v : ans2)
    {
        sum += lower_bound(ans1.begin(), ans1.end(), (mid - 1) / v + 1) - ans1.begin();
        if (v > mid)
            break;
    }
    return sum < m;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n / 2; ++i)
    {
        int x;
        read(x);
        a1.push_back(x);
    }
    for (int i = n / 2 + 1; i <= n; ++i)
    {
        int x;
        read(x);
        a2.push_back(x);
    }
    dfs1(), sort(ans1.begin(), ans1.end());
    dfs2(), sort(ans2.begin(), ans2.end());
    read(m);
    ll l = 0, r = MAX, ans = MAX;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}