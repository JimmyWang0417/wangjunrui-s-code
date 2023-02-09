#include <bits/stdc++.h>
#define int ll
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
const int N = 1e5 + 5;
int n, a[N];
struct Tree_array
{
    int c[N];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
            c[i] += val;
    }
    inline int query(int pos)
    {
        ll res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
} treecnt, treesum;
signed main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    double ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += 0.5 * i * (n - i) * (n - i + 1);
    for (int i = n; i >= 1; --i)
    {
        ans += treecnt.query(a[i]) * (n * n + n - 2 * n * i - 2 * i);
        ans += treesum.query(a[i]) * 2 * i;
        treecnt.update(a[i], 1);
        treesum.update(a[i], i);
    }
    printf("%.9lf\n", ans / n / (n + 1));
    return 0;
}