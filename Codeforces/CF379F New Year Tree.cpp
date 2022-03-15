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
const int N = 1e6 + 10;
int dep[N], fa[N][25];
inline int getlca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = 20; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
inline int getdis(int u, int v)
{
    return dep[u] + dep[v] - dep[getlca(u, v)] * 2;
}
signed main()
{
    int T, n = 4;
    fa[2][0] = fa[3][0] = fa[4][0] = 1;
    dep[1] = 1;
    dep[2] = dep[3] = dep[4] = 2;
    int len = 2, A = 2, B = 3;
    read(T);
    while (T--)
    {
        int u;
        read(u);
        dep[n + 1] = dep[n + 2] = dep[u] + 1;
        fa[n + 1][0] = fa[n + 2][0] = u;
        for (int i = 0; i < 20; ++i)
            fa[n + 1][i + 1] = fa[n + 2][i + 1] = fa[fa[n + 1][i]][i];
        int res = getdis(n + 1, A);
        if (res > len)
        {
            len = res;
            B = n + 1;
        }
        else
        {
            res = getdis(n + 1, B);
            if (res > len)
            {
                len = res;
                A = n + 1;
            }
        }
        n += 2;
        printf("%d\n", len);
    }
    return 0;
}