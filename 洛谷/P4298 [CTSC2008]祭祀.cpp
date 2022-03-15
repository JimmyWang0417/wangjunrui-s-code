#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
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
const int N = 105, M = 1005;
int n, m;
bitset<N> vis, ig, mp[N];
int belong[N];
inline bool find(int u)
{
    for (int v = 1; v <= n; ++v)
        if (mp[u][v] && !vis[v] && !ig[v] && u != v)
        {
            vis[v] = true;
            if (!belong[v] || find(belong[v]))
            {
                belong[v] = u;
                return true;
            }
        }
    return false;
}
bool abled[N], chosen[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        mp[i][i] = true;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        read(u, v);
        mp[u][v] = true;
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (mp[i][k] && mp[k][j])
                    mp[i][j] = true;
    int answer = n;
    for (int i = 1; i <= n; ++i)
    {
        if (find(i))
            --answer;
        vis.reset();
    }
    memset(belong, 0, sizeof(belong));
    for (int i = 1; i <= n; ++i)
    {
        int res = n + 1;
        for (int j = 1; j <= n; ++j)
            if (mp[i][j] || mp[j][i])
            {
                ig[j] = true;
                --res;
            }
        for (int j = 1; j <= n; ++j)
        {
            if (ig[j])
                continue;
            if (find(j))
                --res;
            vis.reset();
        }
        abled[i] = (answer == res);
        memset(belong, 0, sizeof(belong));
        ig.reset();
    }
    for (int i = 1; i <= n; ++i)
        if (abled[i])
        {
            if (vis[i])
                continue;
            chosen[i] = true;
            for (int j = 1; j <= n; ++j)
                if (mp[i][j] || mp[j][i])
                    vis[j] = true;
        }
    printf("%d\n", answer);
    for (int i = 1; i <= n; ++i)
        putchar(chosen[i] + '0');
    putchar('\n');
    for (int i = 1; i <= n; ++i)
        putchar(abled[i] + '0');
    putchar('\n');
    return 0;
}