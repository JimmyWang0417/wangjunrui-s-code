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
constexpr double eps = 1e-7;
int n;
double l, r;
double a[20];
inline double calc(double x)
{
    double res = 0;
    for (int i = 0; i <= n; ++i)
        res = res * x + a[i];
    return res;
}
signed main()
{
    scanf("%d%lf%lf", &n, &l, &r);
    for (int i = 0; i <= n; ++i)
        scanf("%lf", &a[i]);
    while (fabs(r - l) > eps)
    {
        double mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
        if (calc(mid1) < calc(mid2))
            l = mid1;
        else
            r = mid2;
    }
    printf("%lf\n", l);
    return 0;
}