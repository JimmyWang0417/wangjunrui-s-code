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
constexpr int N = 3e3 + 5;
int n;
double p[N][N], pre[N];
double E[N];
bool vis[N];
signed main()
{
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%lf", &p[i][j]);
    for (int i = 1; i < n; ++i)
    {
        E[i] = 1;
        pre[i] = 1 - p[i][n];
    }
    vis[n] = true;
    for (int i = 1; i < n; ++i)
    {
        double res = 1e18;
        int pos = 0;
        for (int j = 1; j < n; ++j)
            if (!vis[j] && E[j] / (1 - pre[j]) < res)
            {
                res = E[j] / (1 - pre[j]);
                pos = j;
            }
        if (pos == 1)
        {
            printf("%lf\n", res);
            return 0;
        }
        vis[pos] = true;
        for (int j = 1; j <= n; ++j)
            if (!vis[j])
            {
                E[j] += res * p[j][pos] * pre[j];
                pre[j] *= (1 - p[j][pos]);
            }
    }
    return 0;
}