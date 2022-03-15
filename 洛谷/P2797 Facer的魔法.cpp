#include <bits/stdc++.h>
#include <bits/extc++.h>
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
const int N = 2e5 + 5;
int n, a[N];
ll sum[N];
inline double calc(int p, int len)
{
    return (double)(sum[p] - sum[p - len - 1] + sum[n] - sum[n - len]) / (len * 2 + 1) - a[p];
}
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + a[i];
    double answer = -1e18;
    for (int i = 1; i <= n; ++i)
    {
        int l = 0, r = min(i - 1, n - i);
        while (l < r - 2)
        {
            int mid1 = l + (r - l + 1) / 3, mid2 = r - (r - l + 1) / 3;
            if (calc(i, mid1) > calc(i, mid2))
                r = mid2;
            else
                l = mid1;
        }
        for (int j = l; j <= r; ++j)
        {
            double res = calc(i, j);
            if (res > answer)
                answer = res;
        }
    }
    printf("%.2lf\n", answer);
    return 0;
}