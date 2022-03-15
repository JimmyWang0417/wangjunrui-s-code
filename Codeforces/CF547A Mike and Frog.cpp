// Problem: A. Mike and Frog
// Contest: Codeforces - Codeforces Round #305 (Div. 1)
// URL: https://codeforces.com/problemset/problem/547/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
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
constexpr int N = 2e6 + 5;
inline void exgcd(int a, int b, int &d, int &x, int &y)
{
    if (b == 0)
    {
        d = a;
        x = 1, y = 0;
    }
    else
    {
        exgcd(b, a % b, d, y, x);
        y -= a / b * x;
    }
}
int mod;
__gnu_pbds::cc_hash_table<int, int> mp;
int g[N];
struct node
{
    int h, a, x, y;
    int begin, cycle;
    inline void work()
    {
        mp.clear();
        mp[g[1] = h] = 1;
        if (g[1] == a)
            begin = 1;
        for (int i = 2;; ++i)
        {
            g[i] = (int)(((ll)g[i - 1] * x + y) % mod);
            if (mp[g[i]])
            {
                if (mp[g[i]] <= begin)
                    cycle = i - mp[g[i]];
                break;
            }
            else if (g[i] == a)
                begin = i;
            mp[g[i]] = i;
        }
    }
    inline void read()
    {
        ::read(h, a, x, y);
    }
    inline void init()
    {
        read();
        work();
    }
} a, b;
signed main()
{
    read(mod);
    a.init(), b.init();
    if (!a.begin || !b.begin)
        printf("-1\n");
    else
    {
        if (!b.cycle)
            swap(a, b);
        if (!a.cycle)
        {
            if (!b.cycle)
            {
                if (a.begin == b.begin)
                    printf("%lld\n", a.begin - 1);
                else
                    printf("-1\n");
            }
            else
            {
                if (a.begin % b.cycle == b.begin % b.cycle && a.begin >= b.begin)
                    printf("%lld\n", a.begin - 1);
                else
                    printf("-1\n");
            }
        }
        else
        {
            if (a.begin > b.begin)
                swap(a, b);
            int d, x, y;
            exgcd(a.cycle, b.cycle, d, x, y);
            if ((b.begin - a.begin) % d)
            {
                printf("-1\n");
                return 0;
            }
            y = -y;
            x *= (b.begin - a.begin) / d;
            y *= (b.begin - a.begin) / d;
            int e = b.cycle / d, f = a.cycle / d;
            if (x < 0 || y < 0)
            {
                int add = max((-x - 1) / e, (-y - 1) / f) + 1;
                x += e * add, y += f * add;
            }
            else
            {
                int del = min(x / e, y / f);
                x -= del * e, y -= del * f;
            }
            printf("%lld\n", a.begin + a.cycle * x - 1);
        }
    }
    return 0;
}