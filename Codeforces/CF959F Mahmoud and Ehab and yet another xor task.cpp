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
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
int d[22];
inline bool insert(int x)
{
    for (int i = 20; i >= 0; --i)
        if ((x >> i) & 1)
        {
            if (d[i])
                x ^= d[i];
            else
            {
                d[i] = x;
                return true;
            }
        }
    return false;
}
inline bool check(int x)
{
    for (int i = 20; i >= 0; --i)
        if ((x >> i) & 1)
            x ^= d[i];
    return !x;
}
int n, m, a[N];
int power[N];
list<pair<int, int>> g[N];
int answer[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
        power[i] = power[i - 1] * 2 % mod;
    for (int i = 1; i <= m; ++i)
    {
        int l, x;
        read(l, x);
        g[l].push_back(make_pair(x, i));
    }
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        res += !insert(a[i]);
        for (auto v : g[i])
            if (check(v.first))
                answer[v.second] = power[res];
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", answer[i]);
    return 0;
}