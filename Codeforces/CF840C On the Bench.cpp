#include <bits/extc++.h>
#include <bits/stdc++.h>
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
const int N = 305;
const int mod = 1e9 + 7;
int n, a[N];
int p[N], tot, cnt[N];
int C[N][N];
ll g[N][N], f[N][N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        int res = 1;
        for (int j = 2; j * j <= a[i]; ++j)
            if (a[i] % j == 0)
            {
                int nmsl = 0;
                while (a[i] % j == 0)
                {
                    a[i] /= j;
                    ++nmsl;
                }
                if (nmsl & 1)
                    res *= j;
            }
        a[i] *= res;
        p[i] = a[i];
    }
    sort(p + 1, p + 1 + n);
    tot = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
        ++cnt[a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p - 1)];

    for (int i = C[0][0] = 1; i <= n; ++i)
    {
        for (int j = C[i][0] = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    g[0][0] = f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            g[i][j] = (g[i - 1][j] * (i - 1 + j) + g[i - 1][j - 1] * j) % mod;
    int sum = 0;
    for (int i = 0; i < tot; ++i)
    {
        for (int j = 0; j <= sum; ++j)
            if (f[i][j])
            {
                for (int k = 1; k <= cnt[i]; ++k)
                    for (int l = 0; l <= j; ++l)
                        (f[i + 1][j + (cnt[i] - k) - l] += f[i][j] * g[cnt[i]][k] % mod * C[j][l] % mod * C[sum + 1 - j][k - l]) %= mod;
            }
        sum += cnt[i];
    }
    printf("%lld\n", f[tot][0]);
    return 0;
}