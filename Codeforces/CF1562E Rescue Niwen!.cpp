// Problem: E. Rescue Niwen!
// Contest: Codeforces - Codeforces Round #741 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1562/E
// Memory Limit: 512 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/extc++.h>
#include <bits/stdc++.h>
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
constexpr int N = 5005;
int n;
char str[N];
int f[N], g[N][N];
inline bool check(int x, int y)
{
    return str[x + g[x][y]] > str[y + g[x][y]];
}
inline void work()
{
    read(n);
    scanf("%s", str + 1);
    for (int i = 1; i < n; ++i)
        g[n][i] = (str[i] == str[n]);
    for (int i = n - 1; i >= 1; --i)
        for (int j = i - 1; j >= 1; --j)
            g[i][j] = (str[i] == str[j] ? g[i + 1][j + 1] + 1 : 0);
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        f[i] = n - i + 1;
        for (int j = i - 1; j >= 1; --j)
            if (check(i, j))
                ckmax(f[i], f[j] + n - i + 1 - g[i][j]);
        ckmax(res, f[i]);
    }
    printf("%d\n", res);
}
signed main()
{
    int T;
    read(T);
    while (T--)
        work();
    return 0;
}