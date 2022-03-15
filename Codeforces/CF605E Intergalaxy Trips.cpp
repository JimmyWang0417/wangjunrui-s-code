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
const int N = 1005;
int n;
double p[N][N], E[N];
double pre[N];
bool vis[N];
signed main()
{
    read(n);
    if (n == 1)
    {
        printf("0\n");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            int x;
            read(x);
            p[i][j] = x * 0.01;
        }
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
        for (int j = 1; j < n; ++j)
            if (!vis[j])
            {
                E[j] += res * p[j][pos] * pre[j];
                pre[j] *= (1 - p[j][pos]);
            }
    }
    return 0;
}