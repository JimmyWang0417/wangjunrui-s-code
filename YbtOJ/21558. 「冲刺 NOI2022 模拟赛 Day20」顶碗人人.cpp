#include <algorithm>
#include <cstdio>
#include <cstring>
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
constexpr int N = 1e5 + 5, M = (1 << 16) + 5;
int n, a[N], dp[M];
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("Ava.in","r",stdin);
    freopen("Ava.out","w",stdout);
#endif
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u, v, w);
        a[u] ^= w, a[v] ^= w;
    }
    int SS = 0, res = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!a[i])
            continue;
        if ((SS >> a[i]) & 1)
        {
            SS ^= (1 << a[i]);
            ++res;
        }
        else
            SS |= (1 << a[i]);
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[SS] = res;
    for (int S = (1 << 16) - 2; S >= 0; S -= 2)
        if (dp[S] < 0x3f3f3f3f)
        {
            for (int i = 1; i <= 15; ++i)
                if ((S >> i) & 1)
                    for (int j = i + 1; j <= 15; ++j)
                        if ((S >> j) & 1)
                        {
                            if ((S >> (i ^ j)) & 1)
                                ckmin(dp[S ^ (1 << i) ^ (1 << j) ^ (1 << (i ^ j))], dp[S] + 2);
                            else
                                ckmin(dp[S ^ (1 << i) ^ (1 << j) ^ (1 << (i ^ j))], dp[S] + 1);
                        }
        }
    printf("%d\n", dp[0]);
    return 0;
}
