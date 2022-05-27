#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 4e5 + 5;
int n, m, q;
int vis[N];
struct node
{
    int x, y;
    inline bool operator<(const node &rhs) const
    {
        return min(vis[x], vis[y]) > min(vis[rhs.x], vis[rhs.y]);
    }
} e[N];
int fa[N];
inline int find(int x)
{
    return !fa[x] ? x : fa[x] = find(fa[x]);
}
int answer[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        read(e[i].x, e[i].y);
        ++e[i].x, ++e[i].y;
    }
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        int x;
        read(x);
        ++x;
        vis[x] = i;
    }
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            vis[i] = q + 1;
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= m; ++i)
    {
        int x = find(e[i].x), y = find(e[i].y);
        if (x == y)
            continue;
        ++answer[min(vis[e[i].x], vis[e[i].y]) - 1];
        fa[x] = y;
    }
    for (int i = q - 1; i >= 0; --i)
        answer[i] += answer[i + 1];
    for (int i = 0; i <= q; ++i)
        printf("%d\n", n - i - answer[i]);
    return 0;
}
