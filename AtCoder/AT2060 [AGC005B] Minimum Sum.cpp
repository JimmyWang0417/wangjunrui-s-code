#include <bits/stdc++.h>
#define ll long long
#define lll __int128
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
constexpr int N = 2e5 + 5;
int n, a[N];
int st[N], top;
int L[N];
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    a[0] = a[n + 1] = INT_MIN;
    for (int i = 1; i <= n; ++i)
    {
        while (a[st[top]] >= a[i])
            --top;
        L[i] = i - st[top];
        st[++top] = i;
    }
    ll res = 0;
    st[top = 0] = n + 1;
    for (int i = n; i >= 1; --i)
    {
        while (a[st[top]] > a[i])
            --top;
        res += (ll)L[i] * (st[top] - i) * a[i];
        st[++top] = i;
    }
    printf("%lld\n", res);
    return 0;
}