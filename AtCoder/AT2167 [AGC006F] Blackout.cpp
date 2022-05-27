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
constexpr int N = 1e5 + 5;
int n, m;
int a[N];
vector<int> g[N], revg[N];
bool ok;
int cnt[4];
inline void dfs(int u)
{
    ++cnt[a[u]];
    for (auto v : g[u])
    {
        ++cnt[0];
        if (!a[v])
        {
            a[v] = a[u] % 3 + 1;
            dfs(v);
        }
        else
        {
            if (a[v] != a[u] % 3 + 1)
                ok = true;
        }
    }
    for (auto v : revg[u])
    {
        if (!a[v])
        {
            a[v] = (a[u] + 1) % 3 + 1;
            dfs(v);
        }
        else
        {
            if (a[v] != (a[u] + 1) % 3 + 1)
                ok = true;
        }
    }
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        g[u].push_back(v);
        revg[v].push_back(u);
    }
    ll answer = 0;
    for (int i = 1; i <= n; ++i)
        if (!a[i])
        {
            a[i] = 1;
            dfs(i);
            if (ok)
                answer += (ll)(cnt[1] + cnt[2] + cnt[3]) * (cnt[1] + cnt[2] + cnt[3]);
            else if (cnt[1] && cnt[2] && cnt[3])
                answer += (ll)cnt[1] * cnt[2] + (ll)cnt[2] * cnt[3] + (ll)cnt[3] * cnt[1];
            else
                answer += cnt[0];
            cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
            ok = false;
        }
    printf("%lld\n", answer);
    return 0;
}