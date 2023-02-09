#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 1e6 + 6;
int n, a[N];
int fa[N], size[N];
struct node
{
    int u, v, w;
    inline bool operator<(const node &rhs) const
    {
        return w < rhs.w;
    }
    inline bool operator>(const node &rhs) const
    {
        return w > rhs.w;
    }
} e[N];
inline int find(int x)
{
    if (!fa[x])
        return x;
    return fa[x] = find(fa[x]);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        size[i] = 1;
    for (int i = 1; i < n; ++i)
    {
        read(e[i].u, e[i].v);
        e[i].w = max(a[e[i].u], a[e[i].v]);
    }
    sort(e + 1, e + n);
    ll ans = 0;
    for (int i = 1; i < n; ++i)
    {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v)
            continue;
        ans += (ll)size[u] * size[v] * e[i].w;
        size[v] += size[u];
        fa[u] = v;
    }
    for (int i = 1; i <= n; ++i)
    {
        size[i] = 1;
        fa[i] = 0;
    }
    for (int i = 1; i < n; ++i)
        e[i].w = min(a[e[i].u], a[e[i].v]);
    sort(e + 1, e + n, greater<node>());
    for (int i = 1; i < n; ++i)
    {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v)
            continue;
        ans -= (ll)size[u] * size[v] * e[i].w;
        size[v] += size[u];
        fa[u] = v;
    }
    printf("%lld\n", ans);
    return 0;
}