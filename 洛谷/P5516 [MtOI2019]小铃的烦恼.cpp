#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
template <typename T>
inline void read(T &x)
{
    x = 0;
    static char s = (char)getchar();
    static bool f = false;
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
const int N = 2e3 + 5;
int n, cnt[26];
char str[N];
double a[N], b[N], f[N];
signed main()
{
    scanf("%s", str + 1);
    n = (int)strlen(str + 1);
    for (int i = 1; i <= n; ++i)
        ++cnt[str[i] - 'A'];
    a[1] = -1, b[1] = 0.5 * n;
    for (int i = 2; i <= n; ++i)
    {
        double inv = 0.5 / i, div = 1 - a[i - 1] * (1 - i) * inv;
        a[i] = -(i + 1) * inv / div;
        b[i] = (n * (n - 1) * inv / (n - i) - b[i - 1] * (1 - i) * inv) / div;
    }
    for (int i = n - 1; i >= 1; --i)
        f[i] = b[i] - a[i] * f[i + 1];
    double ans = 0;
    for (int i = 0; i < 26; ++i)
        ans += f[cnt[i]] * cnt[i] / n;
    printf("%.1lf\n", ans);
    return 0;
}