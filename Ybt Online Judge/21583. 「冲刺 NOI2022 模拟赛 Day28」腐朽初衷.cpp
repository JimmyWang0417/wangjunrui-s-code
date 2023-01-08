// Problem: F. Niyaz and Small Degrees
// Contest: Codeforces - Codeforces Global Round 2
// URL: https://codeforces.com/problemset/problem/1119/F
// Memory Limit: 256 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
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
constexpr int N = 5e5 + 5;
int n;
vector<pair<int, int>> g[N];
struct node
{
    __gnu_pbds::priority_queue<ll> add, del;
    ll sum;
    inline int size()
    {
        return (int)(add.size() - del.size());
    }
    inline void push(ll x)
    {
        add.push(x);
        sum += x;
    }
    inline void pop()
    {
        while (!add.empty() && !del.empty() && add.top() == del.top())
        {
            add.pop();
            del.pop();
        }
        sum -= add.top();
        add.pop();
    }
    inline void erase(ll x)
    {
        del.push(x);
        sum -= x;
    }
    inline ll top()
    {
        while (!add.empty() && !del.empty() && add.top() == del.top())
        {
            add.pop();
            del.pop();
        }
        return add.top();
    }
} q[N];
bool vis[N];
int color;
ll dp[N][2];
ll st[N];
int top;
inline void dfs(int u, int _fa)
{
    vis[u] = true;
    int x = (int)g[u].size() - color;
    while (q[u].size() > x)
        q[u].pop();
    ll sum = 0;
    for (auto e : g[u])
    {
        int &v = e.first;
        if (v == _fa)
            continue;
        if ((int)g[v].size() <= color)
            break;
        dfs(v, u);
        ll w = dp[v][1] + e.second - dp[v][0];
        if (w <= 0)
        {
            sum += dp[v][1] + e.second;
            --x;
        }
        else
        {
            sum += dp[v][0];
            q[u].push(w);
        }
    }
    while (q[u].size() && q[u].size() > x)
    {
        st[++top] = q[u].top();
        q[u].pop();
    }
    dp[u][0] = sum + q[u].sum;
    while (q[u].size() && q[u].size() >= x)
    {
        st[++top] = q[u].top();
        q[u].pop();
    }
    dp[u][1] = sum + q[u].sum;
    while (top)
        q[u].push(st[top--]);
    for (auto e : g[u])
    {
        int &v = e.first;
        if (v == _fa)
            continue;
        if ((int)g[v].size() <= color)
            break;
        ll w = dp[v][1] + e.second - dp[v][0];
        if (w > 0)
            q[u].erase(w);
    }
    // printf("%d %lld %lld %lld\n", u, sum, dp[u][0], dp[u][1]);
}
int id[N];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("decadent.in", "r", stdin);
    freopen("decadent.out", "w", stdout);
#endif
    read(n);
    ll sum = 0;
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        sum += w;
    }
    printf("%lld", sum);
    for (int i = 1; i <= n; ++i)
    {
        id[i] = i;
        sort(g[i].begin(), g[i].end(), [](pair<int, int> x, pair<int, int> y)
             { return g[x.first].size() > g[y.first].size(); });
    }
    sort(id + 1, id + 1 + n, [](int x, int y)
         { return g[x].size() < g[y].size(); });
    color = 1;
    for (int j = 1; color < n; ++color)
    {
        while (j <= n && (int)g[id[j]].size() == color)
        {
            for (auto e : g[id[j++]])
            {
                int &v = e.first;
                if ((int)g[v].size() <= color)
                    break;
                q[v].push(e.second);
            }
        }
        ll res = 0;
        for (int i = j; i <= n; ++i)
        {
            int u = id[i];
            if (vis[u])
                continue;
            dfs(u, 0);
            res += dp[u][0];
        }
        printf(" %lld", res);
        for (int i = j; i <= n; ++i)
            vis[id[i]] = false;
    }
    return 0;
}
