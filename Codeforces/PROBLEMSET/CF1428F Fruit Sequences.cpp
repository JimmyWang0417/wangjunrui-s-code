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
const int N = 5e5 + 5;
int n, f[N];
char str[N];
signed main()
{
    read(n);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i)
        f[i] = n + 1;
    int now = 0;
    ll ans = 0, sum = 0;
    for (int i = n; i >= 1; --i)
    {
        if (str[i] - '0')
        {
            ++now;
            sum += f[now] - i;
        }
        else
            while (now)
            {
                f[now] = i + now;
                --now;
            }
        ans += sum;
    }
    printf("%lld\n", ans);
    return 0;
}