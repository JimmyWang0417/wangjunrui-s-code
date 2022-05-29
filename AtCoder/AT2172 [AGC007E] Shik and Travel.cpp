#include <algorithm>
#include <cstdio>
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
constexpr int N = 131072 + 5;
int n, a[N], lc[N], rc[N];
vector<pair<ll, ll>> g[N], h;
inline void dfs(int u, ll limit)
{
    if (lc[u])
    {
        dfs(lc[u], limit), dfs(rc[u], limit);
        if (g[lc[u]].size() > g[rc[u]].size())
            swap(lc[u], rc[u]);
        auto j = g[rc[u]].rbegin();
        for (auto i = g[lc[u]].begin(); i != g[lc[u]].end(); ++i)
        {
            while (j != g[rc[u]].rend() && i->first + j->first > limit)
                ++j;
            if (j == g[rc[u]].rend())
                break;
            h.push_back(make_pair(i->second + a[u], j->second + a[u]));
            h.push_back(make_pair(j->second + a[u], i->second + a[u]));
        }
        sort(h.begin(), h.end());
        for (auto v : h)
        {
            if (!g[u].empty() && g[u].back().second <= v.second)
                continue;
            g[u].push_back(v);
        }
        h.clear();
        g[lc[u]].clear();
        g[rc[u]].clear();
    }
    else
        g[u].push_back(make_pair(a[u], a[u]));
}
inline bool check(ll mid)
{
    dfs(1, mid);
    if (g[1].empty())
        return false;
    g[1].clear();
    return true;
}
signed main()
{
    int maxx = 0;
    ll sum = 0;
    read(n);
    for (int i = 2; i <= n; ++i)
    {
        int _fa;
        read(_fa, a[i]);
        (lc[_fa] ? rc[_fa] : lc[_fa]) = i;
        sum += a[i];
        ckmax(maxx, a[i]);
    }
    ll l = maxx, r = sum, ans = 0;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}