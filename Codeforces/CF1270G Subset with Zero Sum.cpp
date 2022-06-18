#include <bits/stdc++.h>
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
constexpr int N = 1e6 + 6;
int n, a[N], b[N];
bool vis[N];
int p[N], tot;
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)
        {
            read(a[i]);
            b[i] = i - a[i];
        }
        int x = 1;
        while (!vis[x])
        {
            vis[x] = 1;
            x = b[x];
        }
        p[++tot] = x;
        x = b[x];
        while (x != p[1])
        {
            p[++tot] = x;
            x = b[x];
        }
        printf("%d\n", tot);
        for (int i = 1; i <= tot; ++i)
            printf("%d ", p[i]);
        printf("\n");
        tot = 0;
        fill(vis + 1, vis + 1 + n, 0);
    }
    return 0;
}