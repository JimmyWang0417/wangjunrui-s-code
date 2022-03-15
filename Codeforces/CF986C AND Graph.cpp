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
const int N = (1 << 22) + 5;
int n, m, all, a[N];
bool vis[N], exist[N];
inline void dfs(int u, bool flag)
{
    if (flag)
    {
        if (!exist[u])
            return;
        exist[u] = false;
        dfs(all ^ u, false);
    }
    else
    {
        if (vis[u])
            return;
        vis[u] = true;
        dfs(u, true);
        for (int i = 0; i < n; ++i)
            if ((u >> i) & 1)
                dfs(u ^ (1 << i), false);
    }
}
signed main()
{
    read(n, m);
    all = (1 << n) - 1;
    for (int i = 1; i <= m; ++i)
    {
        read(a[i]);
        exist[a[i]] = true;
    }
    int res = 0;
    for (int i = 1; i <= m; ++i)
        if (!vis[a[i]])
        {
            dfs(a[i], true);
            ++res;
        }
    printf("%d\n", res);
    return 0;
}