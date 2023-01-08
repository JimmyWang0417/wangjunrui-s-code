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
constexpr int N = 2e4 + 5;
constexpr double eps = 1e-10;
int n, m;
struct Point
{
    double x[10];
    Point() { memset(x, 0, sizeof(x)); }
    inline Point operator+(const Point &rhs) const
    {
        Point res;
        for (int i = 0; i < m; ++i)
            res.x[i] = x[i] + rhs.x[i];
        return res;
    }
    inline Point operator-(const Point &rhs) const
    {
        Point res;
        for (int i = 0; i < m; ++i)
            res.x[i] = x[i] - rhs.x[i];
        return res;
    }
    inline double operator*(const Point &rhs) const
    {
        double res = 0;
        for (int i = 0; i < m; ++i)
            res += x[i] * rhs.x[i];
        return res;
    }
    inline Point operator*(const double &rhs) const
    {
        Point res;
        for (int i = 0; i < m; ++i)
            res.x[i] = x[i] * rhs;
        return res;
    }
} point[N], o, q[10], tmp[10];
double g[10][10], answer[10], r;
inline double getdis(const Point &x, const Point &y)
{
    double res = 0;
    for (int i = 0; i < m; ++i)
        res += (x.x[i] - y.x[i]) * (x.x[i] - y.x[i]);
    return sqrt(res);
}
inline void work(int tot)
{
    for (int i = 1; i <= tot; ++i)
    {
        int pos = i;
        for (int j = i + 1; j <= tot; ++j)
            if (fabs(g[j][i]) > fabs(g[pos][i]))
                pos = j;
        if (pos != i)
            swap(g[pos], g[i]);
        for (int j = i + 1; j <= tot; ++j)
        {
            double d = g[j][i] / g[i][i];
            for (int k = i; k <= tot + 1; ++k)
                g[j][k] -= g[i][k] * d;
        }
    }
    for (int i = tot; i >= 1; --i)
    {
        answer[i] = g[i][tot + 1];
        for (int j = i + 1; j <= tot; ++j)
            answer[i] -= answer[j] * g[i][j];
        answer[i] /= g[i][i];
    }
}
inline void dfs(int u, int las)
{
    if (!las)
        return;
    for (int x = 0; x < las; ++x)
    {
        if (getdis(o, point[x]) <= r + eps)
            continue;
        q[u] = point[x];
        for (int i = 1; i < u; ++i)
            tmp[i] = q[i] - q[u];
        for (int i = 1; i < u; ++i)
        {
            g[i][u] = tmp[i] * tmp[i];
            for (int j = 1; j < u; ++j)
                g[i][j] = tmp[i] * tmp[j] * 2;
        }
        work(u - 1), o = q[u];
        for (int i = 1; i < u; ++i)
            o = o + tmp[i] * answer[i];
        r = getdis(o, q[u]);
        if (u <= m)
            dfs(u + 1, x);
    }
}
signed main()
{
    freopen("dimension.in", "r", stdin);
    freopen("dimension.out", "w", stdout);
    read(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%lf", &point[i].x[j]);
    mt19937 rnd((random_device())());
    for (int i = 1; i <= 114514; ++i)
        swap(point[rnd() % n], point[rnd() % n]);
    dfs(1, n);
    for (int i = 0; i < m; ++i)
        printf("%lf ", o.x[i]);
    putchar('\n');
    return 0;
}