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
const int N = 1e6 + 6;
int n, a[N];
ll k;
signed main()
{
    read(n, k);
    ll L = 0, R = 0;
    for (int i = 1; i <= n; ++i)
    {
        L += i;
        R += max(i, n - i + 1);
    }
    if (k < L)
    {
        printf("-1\n");
        return 0;
    }
    if (R <= k)
    {
        printf("%lld\n", R);
        for (int i = 1; i <= n; ++i)
            printf("%d ", i);
        putchar('\n');
        for (int i = n; i >= 1; --i)
            printf("%d ", i);
        putchar('\n');
        return 0;
    }
    printf("%lld\n", k);
    for (int i = 1; i <= n; ++i)
        printf("%d ", i);
    putchar('\n');
    int l = 1, r = n;
    ll sum = L;
    for (int i = 1; i <= n; ++i)
        if (sum + r - i <= k)
        {
            sum += r - i;
            a[i] = r--;
        }
        else
            a[i] = l++;
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
    putchar('\n');
    return 0;
}