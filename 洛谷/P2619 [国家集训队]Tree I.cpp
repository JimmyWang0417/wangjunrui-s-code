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
const int N = 1e5 + 5;
struct node
{
    int u, v, w, color;
    inline bool operator<(const node &rhs) const
    {
        return w == rhs.w ? color < rhs.color : w < rhs.w;
    }
} a[N], b[N];
int n, m, need;
int fa[N];
inline int find(int x)
{
    if (!fa[x])
        return x;
    return fa[x] = find(fa[x]);
}
inline int check(int mid)
{
    for (int i = 1; i <= m; ++i)
    {
        b[i] = a[i];
        b[i].w -= b[i].color * mid;
    }
    sort(b + 1, b + 1 + m);
    int cnt = n - 1;
    for (int i = 1; i <= m; ++i)
    {
        int u = find(b[i].u), v = find(b[i].v);
        if (u == v)
            continue;
        fa[u] = v;
        cnt -= b[i].color;
    }
    memset(fa, 0, sizeof(fa));
    return cnt;
}
inline int solve(int mid)
{
    for (int i = 1; i <= m; ++i)
    {
        b[i] = a[i];
        b[i].w -= b[i].color * mid;
    }
    sort(b + 1, b + 1 + m);
    int res = 0;
    for (int i = 1; i <= m; ++i)
    {
        int u = find(b[i].u), v = find(b[i].v);
        if (u == v)
            continue;
        fa[u] = v;
        res += b[i].w;
    }
    memset(fa, 0, sizeof(fa));
    return (n - 1 - need) * mid + res;
}
signed main()
{
    read(n, m, need);
    for (int i = 1; i <= m; ++i)
    {
        read(a[i].u, a[i].v, a[i].w, a[i].color);
        ++a[i].u, ++a[i].v;
    }
    int l = -200, r = 200;
    int ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        int res = check(mid);
        if (res >= need)
        {
            l = mid + 1;
            ans = solve(mid);
        }
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}