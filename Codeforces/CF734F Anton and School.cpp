#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int ll
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
constexpr int N = 2e5 + 5;
int n, a[N], b[N], c[N];
int cnt[35][2];
signed main()
{
    read(n);
    ll sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(b[i]);
        sum += b[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        read(c[i]);
        sum += c[i];
    }
    if (sum % (2 * n))
    {
        printf("-1\n");
        return 0;
    }
    sum /= 2 * n;
    for (int i = 1; i <= n; ++i)
        if ((b[i] + c[i] - sum) % n)
        {
            printf("-1\n");
            return 0;
        }
    for (int i = 1; i <= n; ++i)
        a[i] = (b[i] + c[i] - sum) / n;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= 30; ++j)
            ++cnt[j][(a[i] >> j) & 1];
    }
    for (int i = 1; i <= n; ++i)
    {
        ll sumb = 0, sumc = 0;
        for (int j = 0; j <= 30; ++j)
        {
            if ((a[i] >> j) & 1)
            {
                sumb += (1ll << j) * cnt[j][1];
                sumc += (1ll << j) * (cnt[j][0] + cnt[j][1]);
            }
            else
                sumc += (1ll << j) * cnt[j][1];
        }
        if (b[i] != sumb || c[i] != sumc)
        {
            printf("-1\n");
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%lld ", a[i]);
    putchar('\n');
    return 0;
}