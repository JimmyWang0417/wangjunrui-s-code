/*正确代码
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
inline void ckmin(int &x, int y)
{
    if (x > y)
        x = y;
}
const int N = 505;
int n, a[N];
int tot, color[N], size[N];
int dp[N][N];
signed main()
{
    color[0]=-1e9;
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        if (color[tot] == x)
            ++size[tot];
        else
        {
            color[++tot] = x;
            size[tot] = 1;
        }
    }
    n = tot;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= n; ++i)
        dp[i + 1][i] = 0;
    for (int i = 1; i <= n; ++i)
        dp[i][i] = (size[i]>=2?1:2);
    for (int len = 2; len <= n; ++len)
    {
        for (int l = 1, r; l + len - 1 <= n; ++l)
        {
            r = l + len - 1;
            for (int i = l; i < r; ++i)
                ckmin(dp[l][r], dp[l][i] + dp[i + 1][r]);
            if (color[l] == color[r])
            {
                ckmin(dp[l][r],dp[l + 1][r - 1]+(size[l]+size[r]<3));
                for (int i = l + 1; i < r; ++i)
                    if (color[l]==color[i]&&(size[l] + size[i] < 3 || size[i] + size[r] < 3))
                        ckmin(dp[l][r], dp[l + 1][i - 1] + dp[i + 1][r - 1]);
            }
        }
    }
    printf("%d\n",dp[1][n]);
    return 0;
}
*/
/* AC代码 */
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
inline void ckmin(int &x, int y)
{
    if (x > y)
        x = y;
}
const int N = 1005;
int n, a[N];
int tot, color[N], size[N];
int dp[N][N];
signed main()
{
    read(n);
    color[0] = -1e9;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        if (color[tot] == x)
            ++size[tot];
        else
        {
            color[++tot] = x;
            size[tot] = 1;
        }
    }
    n = tot;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i)
        dp[i][i] = (size[i] >= 2 ? 1 : 2);
    for (int len = 2; len <= n; ++len)
    {
        for (int l = 1, r; l + len - 1 <= n; ++l)
        {
            r = l + len - 1;
            if (color[l] == color[r])
            {
                ckmin(dp[l][r], dp[l + 1][r - 1] + (size[l] + size[r] < 3));
            }
            for (int i = l; i < r; ++i)
                ckmin(dp[l][r], dp[l][i] + dp[i + 1][r]);
        }
    }
    printf("%d\n", dp[1][n] == 3 ? 2 : dp[1][n]);
    return 0;
}