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
const int N = (1 << 16) + 5;
const int mod = 1e9 + 7;
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
        x -= mod;
}
int n, m, a[N];
bitset<N> mp;
int ans = 1;
inline void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    bool flag = true;
    for (int i = l; i <= mid; ++i)
        flag = (flag && (a[i] == a[i + r - mid]));
    if (flag)
    {
        add(ans, ans);
        solve(l, mid);
    }
    else
    {
        for (int i = l; i <= mid; ++i)
            mp[a[i]] = true;
        for (int i = mid + 1; i <= r; ++i)
            if (mp[a[i]])
            {
                printf("0\n");
                exit(0);
            }
        mp.reset();
        solve(l, mid);
        solve(mid + 1, r);
    }
}
signed main()
{
    read(n, m);
    m = 1 << m;
    for (int i = 0; i < m; ++i)
    {
        read(a[i]);
        mp[a[i]] = true;
    }
    for (int i = 1; i <= n; ++i)
        if (!mp[i])
        {
            printf("0\n");
            return 0;
        }
    mp.reset();
    solve(0, m - 1);
    printf("%d\n", ans);
    return 0;
}
