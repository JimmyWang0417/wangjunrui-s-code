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
constexpr int N = 305;
int n, m;
int a[N][N], head[N];
int cnt[N];
bool vis[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            read(a[i][j]);
        head[i] = 1;
    }
    int ans = INT_MAX;
    for (int kase = 1; kase <= m; ++kase)
    {
        for (int i = 1; i <= n; ++i)
        {
            while (vis[a[i][head[i]]])
                ++head[i];
            ++cnt[a[i][head[i]]];
        }
        int res = 0, maxx = INT_MIN;
        for (int i = 1; i <= m; ++i)
        {
            if (cnt[i] > maxx)
            {
                res = i;
                maxx = cnt[i];
            }
        }
        ckmin(ans, maxx);
        vis[res] = true;
        memset(cnt, 0, sizeof(cnt));
    }
    printf("%d\n", ans);
    return 0;
}