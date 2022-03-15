#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eps 1e-6
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
using namespace std;
const int N = 105;
int n;
double a[N][N], answer[N];
inline void solve()
{
    int cnt = n;
    for (int i = 1; i <= n; ++i)
    {
        int where = i;
        for (int j = i + 1; j <= cnt; ++j)
            if (fabs(a[j][i]) > fabs(a[where][i]))
                where = j;
        if (fabs(a[where][i]) < eps)
        {
            swap(a[++cnt], a[where]);
            continue;
        }
        swap(a[where], a[i]);
        for (int j = i + 1; j <= cnt; ++j)
        {
            double res = a[j][i] / a[i][i];
            for (int k = i; k <= n + 1; ++k)
                a[j][k] -= res * a[i][k];
        }
    }
    for (int i = n; i >= 1; --i)
    {
        if (!a[i][i])
            continue;
        answer[i] = a[i][n + 1];
        for (int j = i + 1; j <= n; ++j)
            answer[i] -= a[i][j] * answer[j];
        answer[i] /= a[i][i];
    }
    if (cnt > n)
    {
        for (int i = 1; i <= cnt; ++i)
        {
            double res = 0;
            for (int j = 1; j <= n; ++j)
                res += a[i][j] * answer[j];
            if (fabs(res - a[i][n + 1]) > eps)
            {
                printf("-1\n");
                return;
            }
        }
        printf("0\n");
    }
    else
        for (int i = 1; i <= n; ++i)
            printf("x%d=%.2lf\n", i, answer[i] + eps);
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n + 1; ++j)
            scanf("%lf", &a[i][j]);
    }
    solve();
    return 0;
}