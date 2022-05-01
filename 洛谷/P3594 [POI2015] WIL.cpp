#include <cstdio>
#define ll long long
#define lll __int128
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
constexpr int N = 2e6 + 5;
int n, d, a[N];
ll p, sum[N], g[N];
int q[N], head = 1, tail;
signed main()
{
    read(n, p, d);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + a[i];
    for (int i = d; i <= n; ++i)
        g[i] = sum[i] - sum[i - d];
    int res = 0;
    for (int i = 1, j = 0; i <= n; ++i)
    {
        if (i - j < d)
            continue;
        while (head <= tail && g[q[tail]] < g[i])
            --tail;
        q[++tail] = i;
        while (j <= i && sum[i] - sum[j] - g[q[head]] > p)
        {
            ++j;
            while (head <= tail && q[head] < j + d)
                ++head;
        }
        ckmax(res, i - j);
    }
    printf("%d\n", res);
    return 0;
}
