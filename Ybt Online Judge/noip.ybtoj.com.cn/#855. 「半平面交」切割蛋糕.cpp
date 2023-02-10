/**
 *    name:     A. 切割蛋糕
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.10 周五 08:14:31 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <algorithm>
#include <cmath>
#include <iostream>
typedef long long ll;
typedef unsigned long long ull;
__extension__ typedef __int128 int128;
constexpr auto lowbit = [](const auto &x)
{ return x & (-x); };

template <typename T>
inline void ckmin(T &_x, T _y)
{
    if (_x > _y)
        _x = _y;
}
template <typename T>
inline void ckmax(T &_x, T _y)
{
    if (_x < _y)
        _x = _y;
}
using namespace std;
constexpr int N = 43;
constexpr double pi = M_PI;
int n, m;
double R;
double c[N], d[N];
double p[N];
struct fuck
{
    double x, y;
    fuck(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    inline fuck operator+(const fuck &rhs) const
    {
        return fuck(x + rhs.x, y + rhs.y);
    }
    inline fuck operator-(const fuck &rhs) const
    {
        return fuck(x - rhs.x, y - rhs.y);
    }
    inline fuck operator*(const double &rhs) const
    {
        return fuck(x * rhs, y * rhs);
    }
    inline double operator*(const fuck &rhs) const
    {
        return x * rhs.x + y * rhs.y;
    }
    inline double operator^(const fuck &rhs) const
    {
        return x * rhs.y - y * rhs.x;
    }
    inline double norm()
    {
        return hypot(x, y);
    }
} a[N], b[N];
int pwp[N], qwq[N];
inline fuck intersection(fuck _a, fuck _b, fuck _c, fuck _d)
{
    double s1 = (_a - _c) ^ (_a - _d), s2 = (_b - _d) ^ (_b - _c);
    return _a + (_a - _b) * (s1 / (s1 + s2));
}
double dis[N];
bool del[N];
bool vis[N];
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("cake.in", "r", stdin);
    freopen("cake.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> R;
    auto calc = [](double alpha)
    {
        return fuck(cos(alpha), sin(alpha));
    };
    for (int i = 1; i <= n; ++i)
    {
        double alpha, beta;
        double h;
        cin >> alpha >> h;
        alpha = alpha / 180 * pi;
        beta = acos((double)h / R);
        c[i] = alpha - beta;
        d[i] = alpha + beta;
        while (c[i] < 0)
            c[i] += 2 * pi;
        while (d[i] >= 2 * pi)
            d[i] -= 2 * pi;
        a[i] = calc(p[++m] = c[i]);
        b[i] = calc(p[++m] = d[i]);
    }
    sort(p + 1, p + 1 + m);
    m = (int)(unique(p + 1, p + 1 + m) - p - 1);
    double other = 2 * pi;
    for (int i = 1; i <= n; ++i)
    {
        pwp[i] = (int)(lower_bound(p + 1, p + 1 + m, c[i]) - p);
        qwq[i] = (int)(lower_bound(p + 1, p + 1 + m, d[i]) - p);
        for (int j = pwp[i]; j != qwq[i]; j = j % m + 1)
            if (!vis[j])
            {
                double now = p[j % m + 1] - p[j];
                if (now < 0)
                    now += 2 * pi;
                other -= now;
                vis[j] = true;
            }
    }
    for (int j = 1; j <= m; ++j)
        vis[j] = false;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = pwp[i]; j != qwq[i]; j = j % m + 1)
            vis[j] = true;
        double l = 0, r = (a[i] - b[i]).norm();
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                if (!vis[pwp[j]] && !vis[qwq[j]])
                    continue;
                if (vis[pwp[j]] && vis[qwq[j]])
                {
                    del[j] = 1;
                    continue;
                }
                auto ccf = (intersection(a[i], b[i], a[j], b[j]) - a[i]).norm();
                if (vis[qwq[j]])
                    l = max(l, ccf);
                else
                    r = min(r, ccf);
            }
        if (l <= r)
            dis[i] = r - l;
        for (int j = 1; j <= m; ++j)
            vis[j] = false;
    }
    double res = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (del[i])
            continue;
        res += dis[i];
    }
    printf("%.10lf %.10lf\n", res * R, other * R);
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}