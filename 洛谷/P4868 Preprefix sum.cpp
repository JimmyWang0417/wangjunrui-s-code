#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i, a, b) for (re int i = a; i <= b; ++i)
#define per(i, a, b) for (re int i = a; i >= b; --i)
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
inline void clear(T *array, int l, int r, int val)
{
    memset(&array[l], val, sizeof(T) * (r - l + 1));
}
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N];
ll pre[N];
struct Tree_array
{
    ll sum[N][2];
    inline void update(int pos, int val)
    {
        for (int i = pos; i <= n; i += lowbit(i))
        {
            sum[i][0] += val;
            sum[i][1] += (ll)val * (pos - 1);
        }
    }
    inline ll query(int pos)
    {
        ll res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += sum[i][0] * pos - sum[i][1];
        return res;
    }
} tree;
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        pre[i] = pre[i - 1] + a[i];
    }
    for (int i = 2; i <= n; ++i)
        pre[i] += pre[i - 1];
    for (int i = 1; i <= m; ++i)
    {
        char opt[10];
        scanf("%s", opt);
        int x;
        read(x);
        if (opt[0] == 'M')
        {
            int y;
            read(y);
            tree.update(x, y - a[x]);
            a[x] = y;
        }
        else
            printf("%lld\n", tree.query(x) + pre[x]);
    }
    return 0;
}
