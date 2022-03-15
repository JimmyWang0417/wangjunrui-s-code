// Problem: P3943 星空
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3943
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int N = 40005, M = 105, K = (1 << 20) + 5;
int n, l, k, a[N];
bitset<N> vis;
vector<int> g;
int dis[M][N];
inline void bfs(int s, int *d)
{
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 1; i <= k; ++i)
        {
            int v = u + a[i];
            if (v <= n + 1 && d[v] > d[u] + 1)
            {
                d[v] = d[u] + 1;
                q.push(v);
            }
            v = u - a[i];
            if (v >= 1 && d[v] > d[u] + 1)
            {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}
int Log[N];
int dp[K];
signed main()
{
    memset(dis, 0x3f, sizeof(dis));
    read(n, l, k);
    for (int i = 1; i <= l; ++i)
    {
        int x;
        read(x);
        vis[x] = true;
    }
    for (int i = 1; i <= n + 1; ++i)
        if (vis[i] != vis[i - 1])
            g.push_back(i);
    for (int i = 1; i <= k; ++i)
        read(a[i]);
    for (int i = 0; i < (int)g.size(); ++i)
        bfs(g[i], dis[i]);
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i < (1 << g.size()); ++i)
    {
        int t = ((1 << g.size()) - 1) ^ i;
        if (t == 0)
        {
            printf("%d\n", dp[i] == 0x3f3f3f3f ? -1 : dp[i]);
            return 0;
        }
        t = (int)log2(t & -t);
        for (int j = t + 1; j < (int)g.size(); ++j)
            if (!(i & (1 << j)))
                dp[i | (1 << t) | (1 << j)] = min(dp[i | (1 << t) | (1 << j)], dp[i] + dis[t][g[j]]);
    }
    return 0;
}