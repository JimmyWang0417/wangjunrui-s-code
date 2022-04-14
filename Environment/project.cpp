#include "guess.h"
#include <cstdio>
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
void init(int subtask_id, int T);
ll solve(ll P, int n)
{
    ll l = 0, r = P - 1;
    lll times = 1, now = 0;
    while (l < r)
    {
        int x = query(0) ^ 2, a = 0;
        while (x)
        {
            ++a;
            x = (x + P % n) % n;
        }
        now = now * n + a;
        times *= n;
        l = (now * P - 1) / times + 1;
        r = ((now + 1) * P - 1) / times;
    }
    ll seed = (times * l) % P;
    l = 1, r = 1e18;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        seed = (seed * n) % P;
        int res = query(mid) ^ (seed % n);
        if (res == 0)
            r = mid - 1;
        else if (res == 1)
            return mid;
        else
            l = mid + 1;
    }
    return 114514;
}