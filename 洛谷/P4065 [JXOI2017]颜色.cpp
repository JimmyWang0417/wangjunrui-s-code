/**
 *    unicode: UTF-8
 *    name:    P4065 [JXOI2017]颜色
 *    author:  wangjunrui
 *    created: 2022.08.09 周二 16:26:43 (Asia/Shanghai)
 **/
#include <cstdio>
#include <random>
#include <unordered_map>
#include <vector>
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
constexpr int N = 3e5 + 5;
int n, a[N];
vector<int> g[N];
ull sum[N];
unordered_map<ull, int> mp;
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)
        {
            read(a[i]);
            g[a[i]].push_back(i);
        }
        mt19937_64 rnd((random_device())());
        for (int i = 1; i <= n; ++i)
        {
            if (g[i].empty())
                continue;
            ull res = 0;
            for (auto u : g[i])
            {
                ull qwq = rnd();
                sum[u] = qwq;
                res ^= qwq;
            }
            sum[g[i].back()] ^= res;
            g[i].clear();
        }
        ull now = 0;
        mp[0] = 1;
        ll res = 0;
        for (int i = 1; i <= n; ++i)
        {
            now ^= sum[i];
            res += mp[now];
            ++mp[now];
        }
        printf("%lld\n", res);
        mp.clear();
    }
    return 0;
}