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
constexpr int N = 505;
constexpr long double eps = 1e-7;
int n;
ll sum[N][N];
inline bool check(pair<int, int> chz, long double ans)
{
    long double minn = 0;
    for (int i = 1; i <= n; ++i)
    {
        long double res = (sum[i][chz.second] - sum[i][chz.first - 1]) - 2 * i * ans;
        if (res - minn >= 2 * (chz.second - chz.first + 1) * ans)
            return true;
        if (minn > res)
            minn = res;
    }
    return false;
}
pair<int, int> point[N * N];
int tot;
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("otto.in", "r", stdin);
    freopen("otto.out", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            int x;
            read(x);
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + x - sum[i - 1][j - 1];
        }
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            point[++tot] = make_pair(i, j);
    mt19937 ni(114514);
    uniform_int_distribution<int> rnd(1, tot);
    for (int i = 1; i <= n * 2; ++i)
        swap(point[rnd(ni)], point[rnd(ni)]);
    long double ans = -1e12;
    for (int i = 1; i <= tot; ++i)
    {
        if (!check(point[i], ans + eps))
            continue;
        long double l = ans + eps, r = 1e12;
        while (fabs(r - l) > eps)
        {
            long double mid = (l + r) / 2;
            if (check(point[i], mid))
            {
                l = mid;
                ans = mid;
            }
            else
                r = mid;
        }
    }
    printf("%.10LF\n", ans);
    return 0;
}
