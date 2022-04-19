#include <bits/stdc++.h>
#define eps 1e-8
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x & (-x))
using namespace std;
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
const int N = 55;
int n;
double a[N][N], answer[N];
double ans = 1;
inline void work()
{
    for (int i = 1; i < n; ++i)
    {
        int where = i;
        for (int j = i + 1; j < n; ++j)
            if (fabs(a[j][i]) > fabs(a[where][i]))
                where = j;
        if (where != i)
        {
            swap(a[where], a[i]);
            ans = -ans;
        }
        for (int j = i + 1; j < n; ++j)
        {
            double res = a[j][i] / a[i][i];
            for (int k = i; k < n; ++k)
                a[j][k] -= res * a[i][k];
        }
        ans *= a[i][i];
    }
}
signed main()
{
#ifdef ONLINE_JUDGE
    freopen("city.in","r",stdin);
    freopen("city.out","w",stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            double lhs;
            scanf("%lf", &lhs);
            if (i == j)
                continue;
            if (lhs > 1 - eps)
                lhs -= eps;
            double rhs = 1 - lhs;
            if (i < j)
                ans *= rhs;
            a[i][j] = -lhs / rhs;
            a[i][i] -= a[i][j];
        }
    work();
    printf("%lf\n", ans);
    return 0;
}