#include <bits/stdc++.h>
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
using namespace std;
const int N = 1e6 + 5;
const int mod = 998244353;
int n, a[N], sum[N];
inline void update(int pos)
{
    for (int i = pos; i <= n; i += lowbit(i))
        ++sum[i];
}
inline int query(int pos)
{
    int res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += sum[i];
    return res;
}
signed main()
{
    read(n);
    for (int i = n; i >= 1; --i)
        read(a[i]);
    ll fac = 1, ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        (ans += (query(a[i] - 1)) * fac) %= mod;
        (fac *= i) %= mod;
        update(a[i]);
    }
    printf("%lld\n", ans + 1);
    return 0;
}