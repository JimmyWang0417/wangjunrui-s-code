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
const int N = 2e5 + 5;
int n, k;
char str[N];
int nxt[N][20];
int dp[N];
inline bool check(int len)
{
    for (int i = 0; i < k; ++i)
    {
        int res = nxt[n + 2][i] = nxt[n + 1][i] = n + 2;
        for (int l, r = n; r >= 1; r = l - 1)
        {
            l = r;
            while (str[l] == '?' || str[l] == 'a' + i)
                --l;
            for (int j = max(l + 1, r - len + 2); j <= r; ++j)
                nxt[j][i] = res;
            for (int j = r - len + 1; j > l; --j)
                nxt[j][i] = j + len;
            if (r - l >= len)
                res = l + len + 1;
            nxt[l][i] = res;
        }
    }
    dp[0] = 1;
    for (int S = 1; S < (1 << k); ++S)
    {
        dp[S] = n + 2;
        for (int i = 0; i < k; ++i)
            if ((S >> i) & 1)
                ckmin(dp[S], nxt[dp[S ^ (1 << i)]][i]);
    }
    return dp[(1 << k) - 1] <= n + 1;
}
signed main()
{
    read(n, k);
    scanf("%s", str + 1);
    int l = 1, r = n / k, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            l = mid + 1;
            ans = mid;
        }
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}