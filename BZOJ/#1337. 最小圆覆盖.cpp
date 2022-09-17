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
constexpr int N = 1e5 + 5;
constexpr double eps = 1e-10;
typedef pair<double, double> node;
int n;
static mt19937 rnd((random_device())());
node a[N];
inline double getdis(node x, node y)
{
    return sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}
int g[5][5];
inline node calco(node a, node b, node c)
{
    double a1, a2, b1, b2, c1, c2;
    node ans;
    a1 = 2 * (b.first - a.first), b1 = 2 * (b.second - a.second),
    c1 = b.first * b.first - a.first * a.first + b.second * b.second - a.second * a.second;
    a2 = 2 * (c.first - a.first), b2 = 2 * (c.second - a.second),
    c2 = c.first * c.first - a.first * a.first + c.second * c.second - a.second * a.second;
    if (fabs(a1) < eps)
    {
        ans.second = c1 / b1;
        ans.first = (c2 - ans.second * b2) / a2;
    }
    else if (fabs(b1) < eps)
    {
        ans.first = c1 / a1;
        ans.second = (c2 - ans.first * a2) / b2;
    }
    else
    {
        ans.first = (c2 * b1 - c1 * b2) / (a2 * b1 - a1 * b2);
        ans.second = (c2 * a1 - c1 * a2) / (b2 * a1 - b1 * a2);
    }
    return ans;
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf%lf", &a[i].first, &a[i].second);
    for (int i = 1; i <= 1919810; ++i)
        swap(a[rnd() % n + 1], a[rnd() % n + 1]);
    node o = a[1];
    double r = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (getdis(o, a[i]) <= r + eps)
            continue;
        o.first = (a[1].first + a[i].first) / 2;
        o.second = (a[1].second + a[i].second) / 2;
        r = getdis(o, a[1]);
        for (int j = 2; j < i; ++j)
        {
            if (getdis(o, a[j]) <= r + eps)
                continue;
            o.first = (a[i].first + a[j].first) / 2;
            o.second = (a[i].second + a[j].second) / 2;
            r = getdis(o, a[i]);
            for (int k = 1; k < j; ++k)
            {
                if (getdis(o, a[k]) <= r + eps)
                    continue;
                o = calco(a[i], a[j], a[k]);
                r = getdis(o, a[i]);
            }
        }
    }
    printf("%.3lf\n", r);
    return 0;
}