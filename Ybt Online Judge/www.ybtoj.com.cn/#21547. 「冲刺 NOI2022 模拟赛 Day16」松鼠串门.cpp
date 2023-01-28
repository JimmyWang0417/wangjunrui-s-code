#include <algorithm>
#include <cstdio>
#include <vector>
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
constexpr int N = 5e5 + 5;
int n, m;
int dep[N * 2];
struct node
{
    pair<ull, int> d[64];
    inline void insert(pair<ull, int> val)
    {
        for (int i = 63; i >= 0; --i)
            if ((val.first >> i) & 1)
            {
                if (d[i].first)
                {
                    if (val.second > d[i].second)
                        swap(val, d[i]);
                    val.first ^= d[i].first;
                }
                else
                {
                    d[i] = val;
                    break;
                }
            }
    }
    inline ull calc(int depth)
    {
        ull res = 0;
        for (int i = 63; i >= 0; --i)
            if ((res ^ d[i].first) > res && depth <= d[i].second)
                res ^= d[i].first;
        return res;
    }
} a[N * 2];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int f;
        ull v;
        read(f, v);
        a[i] = a[f];
        a[i].insert(make_pair(v, dep[i] = dep[f] + 1));
    }
    for (int i = 1; i <= m; ++i)
    {
        int opt, u;
        read(opt, u);
        if (opt)
        {
            ull v;
            read(v);
            ++n;
            a[n] = a[u];
            a[n].insert(make_pair(v, dep[n] = dep[u] + 1));
        }
        else
        {
            int v;
            read(v);
            printf("%llu\n", a[u].calc(dep[u] - v));
        }
    }
    return 0;
}