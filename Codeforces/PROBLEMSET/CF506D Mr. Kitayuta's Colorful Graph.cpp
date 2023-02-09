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
int n, m, q;
unordered_map<int, int> fa[N], answer[N];
inline int find(int x, int color)
{
    if (fa[x][color] == x)
        return x;
    return fa[x][color] = find(fa[x][color], color);
}
inline void merge(int x, int y, int color)
{
    if (!fa[x].count(color))
        fa[x][color] = x;
    if (!fa[y].count(color))
        fa[y][color] = y;
    x = find(x, color);
    y = find(y, color);
    if (x != y)
        fa[x][color] = y;
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        read(u, v, w);
        merge(u, v, w);
    }
    read(q);
    for (int i = 1; i <= q; ++i)
    {
        int u, v;
        read(u, v);
        if (fa[u].size() > fa[v].size())
            swap(u, v);
        if (answer[u].count(v))
        {
            printf("%d\n", answer[u][v]);
            continue;
        }
        int res = 0;
        for (auto t : fa[u])
            res += (fa[v].count(t.first) && find(u, t.first) == find(v, t.first));
        printf("%d\n", answer[u][v] = res);
    }
    return 0;
}