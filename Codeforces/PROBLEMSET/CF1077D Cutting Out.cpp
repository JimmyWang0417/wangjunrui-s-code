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
const int N = 2e5 + 5;
int n, m;
pair<int, int> a[N];
inline bool check(int val)
{
    int res = 0;
    for (int i = 1; i <= n; ++i)
        res += a[i].first / val;
    return res >= m;
}
inline void solve(int val)
{
    for (int i = 1; i <= n; ++i)
    {
        while (a[i].first >= val && m)
        {
            printf("%d ", a[i].second);
            a[i].first -= val;
            --m;
        }
    }
    putchar('\n');
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        read(x);
        ++a[x].first;
    }
    for (int i = 1; i <= 2e5; ++i)
        a[i].second = i;
    sort(a + 1, a + 1 + 200000, greater<pair<int, int>>());

    for (n = 1; a[n].second; ++n)
        ;
    --n;

    int l = 1, r = n, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    solve(ans);
    return 0;
}
