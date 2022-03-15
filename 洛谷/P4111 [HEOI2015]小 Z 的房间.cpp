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
const int N = 9 * 9 + 5;
const int mod = 1e9;
int n, m, tot;
char str[15][15];
int id[N][N];
ll a[N][N], answer[N];
inline void work()
{
    int cnt = n * m - 1;
    ll ans = 1;
    for (int i = 1; i < tot; ++i)
    {
        for (int j = i + 1; j < tot; ++j)
            while (a[j][i])
            {
                ll t = a[i][i] / a[j][i];
                for (int k = i; k <= cnt; ++k)
                    (a[i][k] -= a[j][k] * t % mod) %= mod;
                swap(a[i], a[j]);
                ans = -ans;
            }
        (ans *= a[i][i]) %= mod;
    }
    printf("%lld\n", (ans + mod) % mod);
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        scanf("%s", str[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (str[i][j] == '.')
                id[i][j] = ++tot;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (str[i][j] == '.')
            {
                if (j < m && str[i][j + 1] == '.')
                {
                    int x = id[i][j], y = id[i][j + 1];
                    ++a[x][x], ++a[y][y];
                    --a[x][y], --a[y][x];
                }
                if (i < n && str[i + 1][j] == '.')
                {
                    int x = id[i][j], y = id[i + 1][j];
                    ++a[x][x], ++a[y][y];
                    --a[x][y], --a[y][x];
                }
            }
    work();
    return 0;
}