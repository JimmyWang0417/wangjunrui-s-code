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
constexpr int N = 2e5 + 5;
constexpr int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
inline void dec(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += mod;
}
int n;
map<ll, int> mp;
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        mp[0] = 1;
        read(n);
        ll sum = 0;
        int ans = 1;
        for (int i = 1; i <= n; ++i)
        {
            int v;
            read(v);
            int cjtcalc = ans;
            dec(cjtcalc, mp[-sum]);
            add(mp[-sum], cjtcalc);
            add(ans, cjtcalc);
            sum += v;
        }
        printf("%d\n", ans);
        mp.clear();
    }
    return 0;
}