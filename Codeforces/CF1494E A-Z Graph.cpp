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
const int N = 2e5 + 5;
__gnu_pbds::gp_hash_table<ll, char> mp;
int n, m;
#define calc(x, y) ((ll)(x)*n + (y))
signed main()
{
    read(n, m);
    int a = 0, b = 0;
    for (int i = 1; i <= m; ++i)
    {
        char opt[10];
        scanf("%s", opt);
        if (opt[0] == '+')
        {
            int u, v;
            read(u, v);
            scanf("%s", opt);
            auto it = mp.find(calc(v, u));
            if (it != mp.end())
            {
                ++a;
                if (it->second == opt[0])
                    ++b;
            }
            mp[calc(u, v)] = opt[0];
        }
        else if (opt[0] == '-')
        {
            int u, v;
            read(u, v);
            auto it = mp.find(calc(v, u));
            if (it != mp.end())
            {
                --a;
                if (it->second == mp[calc(u, v)])
                    --b;
            }
            mp.erase(calc(u, v));
        }
        else
        {
            int k;
            read(k);
            if (k & 1)
                puts(a ? "YES" : "NO");
            else
                puts(b ? "YES" : "NO");
        }
    }
    return 0;
}