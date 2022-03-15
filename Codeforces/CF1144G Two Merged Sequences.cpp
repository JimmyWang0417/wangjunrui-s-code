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
int n, a[N];
pair<int, bool> dp[N][2];
bool answer[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    dp[1][0] = make_pair(N, true), dp[1][1] = make_pair(-1, true);
    for (int i = 2; i <= n; ++i)
    {
        dp[i][0] = make_pair(-1, false), dp[i][1] = make_pair(N, false);
        if (a[i - 1] < a[i])
            ckmax(dp[i][0], make_pair(dp[i - 1][0].first, false));
        else if (a[i] < a[i - 1])
            ckmin(dp[i][1], make_pair(dp[i - 1][1].first, true));
        if (dp[i - 1][1].first < a[i])
            ckmax(dp[i][0], make_pair(a[i - 1], true));
        if (dp[i - 1][0].first > a[i])
            ckmin(dp[i][1], make_pair(a[i - 1], false));
    }
    if (dp[n][0].first > -1)
    {
        puts("YES");
        answer[n] = false;
        for (int i = n; i > 1; --i)
            answer[i - 1] = dp[i][answer[i]].second;
        for (int i = 1; i <= n; ++i)
            printf("%d ", answer[i]);
        putchar('\n');
    }
    else if (dp[n][1].first < N)
    {
        puts("YES");
        answer[n] = true;
        for (int i = n; i > 1; --i)
            answer[i - 1] = dp[i][answer[i]].second;
        for (int i = 1; i <= n; ++i)
            printf("%d ", answer[i]);
        putchar('\n');
    }
    else
        puts("NO");
    return 0;
}