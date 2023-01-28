#include <cstdio>
#include <vector>
#define size nmsl
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
constexpr int N = 2e5 + 5;
constexpr int mod = 998244353;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, a[N], b[N], A[N], B[N];
vector<int> g[N];
bool vis[N];
int size;
inline void dfs(int u)
{
    if (vis[u])
        return;
    ++size;
    vis[u] = true;
    for (auto v : g[u])
        dfs(v);
}
int dp[N];
inline ll solve(int val)
{
    if (val == 1)
        return 1;
    return (dp[val] + 2 * dp[val - 1] % mod) % mod;
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    for (int i = 1; i <= n; ++i)
        A[a[i]] = B[b[i]] = i;
    for (int i = 1; i <= n; ++i)
    {
        g[A[i]].push_back(B[i]);
        g[B[i]].push_back(A[i]);
    }
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        dp[i] = dp[i - 1];
        add(dp[i], dp[i - 2]);
    }
    ll answer = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (vis[i])
            continue;
        size = 0;
        dfs(i);
        (answer *= solve(size)) %= mod;
    }
    printf("%lld\n", answer);
    return 0;
}
