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
constexpr int N = 2005;
constexpr double pi = __gnu_cxx::__math_constants<double>::__pi;
int n, m;
pair<double, double> a[N];
double b[N], c[N];
int answer;
inline void solve(int len)
{
    int tot = 0;
    c[++tot] = b[1];
    for (int i = 2; i <= len; ++i)
    {
        if (b[i] > c[tot])
        {
            c[++tot] = b[i];
            continue;
        }
        *upper_bound(c + 1, c + tot + 1, b[i]) = b[i];
    }
    ckmax(answer, tot);
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("circle.in", "r", stdin);
    freopen("circle.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        read(x, y);
        double dis = sqrt(x * x + y * y);
        double alpha = atan2(y, x), beta = acos(m / dis);
        double l = alpha - beta, r = alpha + beta;
        while (l <= -pi)
            l += 2 * pi;
        while (r > pi)
            r -= 2 * pi;
        if (l > r)
            swap(l, r);
        a[i] = make_pair(l, r);
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
    {
        int len = 0;
        for (int j = i + 1; j <= n; ++j)
            if (a[i].second >= a[j].first && a[j].second >= a[i].second)
                b[++len] = a[j].second;
        solve(len);
    }
    printf("%d\n", answer + 1);
    return 0;
}
