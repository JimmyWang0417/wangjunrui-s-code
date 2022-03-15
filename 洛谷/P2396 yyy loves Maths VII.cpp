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
using namespace std;
const int N = 30, M = (1 << 24) + 5;
const int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
ll dis[M];
int dp[M];
int n, m;
signed main()
{
    read(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        read(x);
        for (int S = 0; S < (1 << i); ++S)
            dis[S | (1 << i)] = dis[S] + x;
    }
    dp[0] = 1;
    read(m);
    int b[2] = {-1, -1};
    for (int i = 0; i < m; ++i)
        read(b[i]);
    for (int S = 1; S < (1 << n); ++S)
    {
        if (dis[S] == b[0] || dis[S] == b[1])
            continue;
        for (int G = S; G; G ^= lowbit(G))
            add(dp[S], dp[S ^ lowbit(G)]);
    }
    printf("%d\n", dp[(1 << n) - 1]);
    return 0;
}