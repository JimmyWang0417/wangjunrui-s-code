// Problem: B. Bricks
// Contest: Codeforces - 2017-2018 ACM-ICPC Southeastern European Regional Programming Contest (SEERC 2017)
// URL: https://codeforces.com/gym/101669/problem/B
// Memory Limit: 512 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
int n, m;
int a[N];
int nmsl[N * 2], *mp = &nmsl[N];
int dp[N];
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int x;
        read(x);
        ++a[x];
    }
    dp[0] = 1;
    mp[0] = 1;
    for (int i = 1; i <= n + 1; ++i)
    {
        if (a[i])
            a[i] += a[i - 1];
        else
        {
            a[i] += a[i - 1];
            dp[i] = mp[a[i - 1] - (i - 1)];
            mp[a[i] - i] += dp[i];
            if (mp[a[i] - i] >= mod)
                mp[a[i] - i] -= mod;
        }
    }
    printf("%d\n", dp[n + 1]);
    return 0;
}
