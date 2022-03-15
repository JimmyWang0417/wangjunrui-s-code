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
const int N = 1e6 + 5;
int n, m, q, belong[N], truebelong[N];
bool exist[N];
pair<int, int> a[N];
int cnt, tot;
vector<int> f[N], g[N], h[N];
int color[N];
bool flag;
inline void dfs(int u, int col)
{
    if (color[u])
    {
        if (color[u] != col)
            flag = true;
        return;
    }
    truebelong[u] = cnt;
    color[u] = col;
    for (auto v : h[u])
        dfs(v, 3 - col);
}
int truecolor[N];
bool nmsl;
inline void check(int u, int col)
{
    if (truecolor[u])
    {
        if (truecolor[u] != col)
            flag = true;
        return;
    }
    truecolor[u] = col;
    for (auto v : g[u])
        check(v, 3 - col);
}
signed main()
{
    read(n, m, q);
    for (int i = 1; i <= n; ++i)
    {
        read(belong[i]);
        f[belong[i]].push_back(i);
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        if (belong[u] == belong[v])
        {
            h[u].push_back(v);
            h[v].push_back(u);
        }
        else
        {
            if (belong[u] > belong[v])
                swap(u, v);
            a[++tot] = make_pair(u, v);
        }
    }
    int sum = 0;
    for (int i = 1; i <= q; ++i)
    {
        flag = false;
        for (auto u : f[i])
            if (!color[u])
            {
                ++cnt;
                dfs(u, 1);
            }
        exist[i] = flag;
        sum += !flag;
    }
    ll answer = (ll)sum * (sum - 1) / 2;
    sort(a + 1, a + 1 + tot, [](const pair<int, int> &x, const pair<int, int> &y)
         { return belong[x.first] == belong[y.first] ? belong[x.second] < belong[y.second] : belong[x.first] < belong[y.first]; });
    for (int l = 1, r; l <= tot; l = r)
    {
    	nmsl=(belong[a[l].first] ==7&&belong[a[l].second]==10);
        r = l + 1;
        while (r <= tot && belong[a[l].first] == belong[a[r].first] && belong[a[l].second] == belong[a[r].second])
            ++r;
        if (exist[belong[a[l].first]] || exist[belong[a[l].second]])
            continue;
        for (int i = l; i < r; ++i)
        {
            if (color[a[i].first] == color[a[i].second])
            {
                ++cnt;
                g[truebelong[a[i].first]].push_back(cnt);
                g[truebelong[a[i].second]].push_back(cnt);
                g[cnt].push_back(truebelong[a[i].first]);
                g[cnt].push_back(truebelong[a[i].second]);
            }
            else
            {
                g[truebelong[a[i].first]].push_back(truebelong[a[i].second]);
                g[truebelong[a[i].second]].push_back(truebelong[a[i].first]);
            }
        }
        flag = false;
        for (int i = l; i < r; ++i)
            if (!truecolor[truebelong[a[i].first]])
                check(truebelong[a[i].first], 1);
        for (int i = l; i < r; ++i)
        {
            g[truebelong[a[i].first]].clear();
            g[truebelong[a[i].second]].clear();
            truecolor[truebelong[a[i].first]] = truecolor[truebelong[a[i].second]] = 0;
        }
        answer -= flag;
    }
    printf("%lld\n", answer);
    return 0;
}