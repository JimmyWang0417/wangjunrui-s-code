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
constexpr int N = 1e5 + 5;
constexpr int mod = 998244353;
int n, k;
struct node
{
    int d[10];
    inline bool insert(int val)
    {
        for (int i = 9; i >= 0; --i)
            if ((val >> i) & 1)
            {
                if (d[i])
                    val ^= d[i];
                else
                {
                    d[i] = val;
                    return true;
                }
            }
        return false;
    }
} d[15];
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int tot;
pair<int, int> a[N];
int fa[N];
int b[N];
int mp[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline void calc(int u, int _fa)
{
    for (int i = head[u]; i; i = edge[i].next)
    {
        int &v = edge[i].to;
        if (v == _fa)
            continue;
        calc(v, u);
        b[u] ^= b[v];
    }
    ++mp[b[u]];
}
pair<int, int> c[N];
ll answer = 1;
inline void dfs(int u, int las, ll now, node ans)
{
    if (las == tot + 1)
        return;
    dfs(u, las + 1, now, ans);
    if (!ans.insert(c[las].first))
        return;
    (now *= c[las].second) %= mod;
    (answer += now) %= mod;
    if (u < k)
        dfs(u + 1, las + 1, now, ans);
}
signed main()
{
    freopen("connected.in", "r", stdin);
    freopen("connected.out", "w", stdout);
    read(n, k);
    for (int i = 1; i < n + k; ++i)
    {
        int u, v;
        read(u, v);
        if (find(u) == find(v))
            a[tot++] = make_pair(u, v);
        else
        {
            add_edge(u, v);
            add_edge(v, u);
            fa[find(u)] = find(v);
        }
    }
    for (int i = 0; i < k; ++i)
    {
        b[a[i].first] ^= 1 << i;
        b[a[i].second] ^= 1 << i;
        ++mp[1 << i];
    }
    calc(1, 0);
    tot = 0;
    for (int i = 1; i < (1 << k); ++i)
        if (mp[i])
            c[++tot] = make_pair(i, mp[i]);
    dfs(1, 1, 1, node());
    printf("%lld\n", answer);
    return 0;
}