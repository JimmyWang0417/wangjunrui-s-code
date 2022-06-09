#include <algorithm>
#include <cstdio>
#include <unordered_map>
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
constexpr int N = 4e5 + 5;
int n;
int a[N], b[N];
int p[N], tot;
unordered_map<int, int> mp;
bool vis[N];
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        a[n + 1] ^= a[i];
        ++mp[a[i]];
    }
    ++mp[a[n + 1]];
    for (int i = 1; i <= n; ++i)
    {
        read(b[i]);
        b[n + 1] ^= b[i];
        --mp[b[i]];
    }
    --mp[b[n + 1]];
    ++n;
    for (auto u : mp)
        if (u.second)
        {
            puts("-1");
            return 0;
        }
    for (int i = 1; i <= n; ++i)
        p[++tot] = a[i];
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    int res = 0;
    for (int i = 1; i < n; ++i)
        if (a[i] != b[i])
            ++res;
    if (!res)
    {
        printf("0\n");
        return 0;
    }
    for (int i = 1; i < n; ++i)
        if (a[i] != b[i])
        {
            int x = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p),
                y = (int)(lower_bound(p + 1, p + 1 + tot, b[i]) - p);
            vis[x] = vis[y] = true;
            if (find(x) != find(y))
                fa[find(x)] = find(y);
        }
    for (int i = 1; i <= tot; ++i)
        if (!fa[i] && vis[i])
            ++res;
    if (vis[lower_bound(p + 1, p + 1 + tot, a[n]) - p])
        --res;
    printf("%d\n", res);
    return 0;
}