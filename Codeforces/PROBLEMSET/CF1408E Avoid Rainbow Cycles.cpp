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
const int N = 2e5 + 5;
int n, m, a[N], b[N];
struct node
{
    int u, v, w;
    node(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
    inline bool operator>(const node &rhs) const
    {
        return w > rhs.w;
    }
} e[N];
int tot;
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
signed main()
{
    read(m, n);
    for (int i = 1; i <= m; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    ll ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        int cnt;
        read(cnt);
        while (cnt--)
        {
            int x;
            read(x);
            e[++tot] = node(i + n, x, a[i] + b[x]);
            ans += e[tot].w;
        }
    }
    sort(e + 1, e + 1 + tot, greater<node>());
    for (int i = 1; i <= tot; ++i)
    {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v)
            continue;
        fa[u] = v;
        ans -= e[i].w;
    }
    printf("%lld\n", ans);
    return 0;
}