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
const int N = 1e5 + 5;
int n, len;
char str[N];
struct node
{
    char lcolor, rcolor;
    int suf, pre, ans;
    bool flag;
    inline void clear()
    {
        suf = pre = ans = flag = 0;
    }
} dp[2];
signed main()
{
    read(n);
    scanf("%s", str + 1);
    len = (int)strlen(str + 1);
    bool flag = true;
    for (int i = 1, las = 1; i <= len; ++i)
    {
        if (i != 1 && str[i] != str[i - 1])
        {
            las = i;
            flag = false;
        }
        dp[1].ans = max(dp[1].ans, i - las + 1);
    }
    dp[1].flag = flag;
    dp[1].lcolor = str[1], dp[1].rcolor = str[len];
    dp[1].pre = dp[1].suf = 1;
    while (str[dp[1].pre + 1] == dp[1].lcolor)
        ++dp[1].pre;
    while (str[len - dp[1].suf] == dp[1].rcolor)
        ++dp[1].suf;
    printf("%d\n", dp[1].ans);
    while (--n)
    {
        swap(dp[0], dp[1]);
        scanf("%s", str + 1);
        len = (int)strlen(str + 1);
        dp[1].lcolor = dp[0].lcolor, dp[1].rcolor = dp[0].rcolor;
        if (dp[0].flag)
        {
            flag = true;
            dp[1].ans = dp[0].ans;
            for (int i = 1, now = 0; i <= len; ++i)
            {
                if (i != 1 && str[i] == dp[0].rcolor)
                {
                    now = dp[0].ans;
                    flag = false;
                }
                now += 1 + dp[0].ans;
                dp[1].ans = now;
            }
            dp[1].flag = flag;
            int now = 0;
            for (dp[1].pre = dp[0].ans, now = 0; str[now + 1] == dp[0].lcolor; ++now, dp[1].pre += 1 + dp[0].ans)
                ;
            for (dp[1].suf = dp[0].ans, now = 0; str[len - now] == dp[0].lcolor; ++now, dp[1].pre += 1 + dp[0].ans)
                ;
        }
        else
        {
            dp[1].ans = dp[0].ans;
            dp[1].pre = dp[0].pre, dp[1].suf = dp[0].suf;
            for (int i = 1; i <= len; ++i)
                if (dp[0].rcolor == str[i] && str[i] == dp[0].lcolor)
                    dp[1].ans = max(dp[1].ans, dp[0].suf + 1 + dp[0].pre);
        }
    }
    printf("%d\n", dp[1].ans);
    return 0;
}
